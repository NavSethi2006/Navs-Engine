#include "tilemap.h"

void* map_texture_loader(const char *path) {
	Texture tex = get_texture_asset(path);
	return (void*)tex.Image;
}

TileMap* load_tmx_map(const char *map_path,int x, int y, bool draw_debug_for_obj_layer) {
    TileMap *map = malloc(sizeof(TileMap));
    if (!map) {
        fprintf(stderr, "ERROR: Could not allocate memory for TileMap.\n");
        return NULL;
    }
	printf("Map Initilzed\n");
    map->map = tmx_load(map_path);
    if (!map->map) {
        fprintf(stderr, "TMX Load Error: %s\n", tmx_strerr());
        return NULL;
    }
	printf("TMX loaded\n");
    map->x = x;
    map->y = y;
	map->layer = map->map->ly_head;
	map->tiles = map->map->tiles;
	map->Debug_lines = draw_debug_for_obj_layer;
	return map;
}

SDL_Color tmx_to_sdl_color(unsigned int color) {
	SDL_Color c;
	c.a = (color >> 24) & 0xFF;
	c.b = (color >> 16) & 0xFF;
	c.g = (color >> 8) & 0xFF;
	c.r = (color) & 0xFF;
	return c;
}

void draw_tile(Window *window, TileMap *map, tmx_tile *tile, int x, int y) {
    if (!tile || !tile->tileset || !tile->tileset->image) 
        return;

    map->tileset.Image = (SDL_Texture*)tile->tileset->image->resource_image;

    SDL_FRect dest = {x + map->x, y + map->y, tile->tileset->tile_width, tile->tileset->tile_height};
    SDL_FRect src = {tile->ul_x, tile->ul_y, tile->tileset->tile_width, tile->tileset->tile_height};
    

    render_with_size_and_rect(&map->tileset, window, &src, &dest);
}

void render_tile_layer(Window *window, TileMap *map) {
    for (unsigned long y = 0; y < map->map->height; y++) {
        for (unsigned long x = 0; x < map->map->width; x++) {
            unsigned int gid = map->layer->content.gids[(y * map->map->width) + x];
            gid &= TMX_FLIP_BITS_REMOVAL;
            
            if (gid) {
                draw_tile(
                    window,
                    map,
                    map->tiles[gid],
                    x * map->map->tile_width,
                    y * map->map->tile_height
                );
            }
        }
    }
}

void render_image_layer(Window *window, TileMap *map) {
    if (!map->layer->content.image) return;
    SDL_Texture *tex = (SDL_Texture*)map->layer->content.image->resource_image;

    SDL_FRect dest = {
        .x = map->x + (map->layer->offsetx * map->scale),  // Scaled offset
        .y = map->y + (map->layer->offsety * map->scale),
        .w = map->layer->content.image->width * map->scale,  // Scaled size
        .h = map->layer->content.image->height * map->scale
    };

    SDL_RenderTexture(window->renderer, tex, NULL, &dest);
}

void render_object_layer(Window *window, TileMap *map, tmx_object_group *group) {
    tmx_object *obj = group->head;
    while (obj) {
        if (obj->visible && obj->obj_type == OT_SQUARE) {
            SDL_FRect rect = {
                .x = map->x + (obj->x * map->scale),  // Scaled position
                .y = map->y + (obj->y * map->scale),
                .w = obj->width * map->scale,         // Scaled size
                .h = obj->height * map->scale
            };
            if(map->Debug_lines) {
                SDL_RenderRect(window->renderer, &rect);
            }
        }
        obj = obj->next;
    }
}

void render_layers(Window *window, TileMap *map, tmx_layer *layer) {
	while (layer) {
		if (!layer->visible) {
			layer = layer->next;
			continue;
		}

		switch (layer->type) {
			case L_LAYER:
				render_tile_layer(window, map);
				break;
			case L_IMAGE:
				render_image_layer(window, map);
				break;
			case L_OBJGR:
			
				render_object_layer(window, map, layer->content.objgr);
				break;
			
			case L_GROUP:
				render_layers(window, map, layer->content.group_head);
				break;
		}
		layer = layer->next;
	}
}

void render_tmx_map(Window *window, TileMap *map) {

	render_layers(window, map, map->map->ly_head);

}

void free_tmx_map(TileMap *map) {
	if (!map) return;

    if (map->map) {
        tmx_map_free(map->map); // Free TMX internal structures
        map->map = NULL;
    }

    free(map);
	
}
