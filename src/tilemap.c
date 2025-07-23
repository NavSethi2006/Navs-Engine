#include "tilemap.h"

void* map_texture_loader(const char *path) {
	Texture tex = get_texture_asset(path);
	return (void*)tex.Image; // SDL_Texture* as void*
}

// Load TMX map
tmx_map* load_tmx_map(const char *path) {
	tmx_map *map = tmx_load(path);
	if (!map) {
		fprintf(stderr, "TMX Load Error: %s\n", tmx_strerr());
	}
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

// Draw a single tile at world position + offset
void draw_tile(Window *window, tmx_tile *tile, int x, int y, float offset_x, float offset_y) {
	if (!tile || !tile->tileset || !tile->tileset->image)
		return;

	SDL_Texture *texture = (SDL_Texture*)tile->tileset->image->resource_image;
	int tw = tile->tileset->tile_width;
	int th = tile->tileset->tile_height;

	SDL_FRect dest = {
		.x = x + offset_x,
		.y = y + offset_y,
		.w = tw,
		.h = th
	};

	SDL_FRect src = { tile->ul_x, tile->ul_y, tw, th };
	SDL_RenderTexture(window->renderer, texture, &src, &dest);
}

// Render tile layers with offset
void render_tile_layer(Window *window, tmx_map *map, tmx_layer *layer, float offset_x, float offset_y) {
	for (unsigned long y = 0; y < map->height; y++) {
		for (unsigned long x = 0; x < map->width; x++) {
			unsigned int gid = layer->content.gids[y * map->width + x];
			gid &= TMX_FLIP_BITS_REMOVAL;

			if (gid) {
				draw_tile(
					window,
					map->tiles[gid],
					x * map->tile_width,
					y * map->tile_height,
					offset_x,
					offset_y
				);
			}
		}
	}
}

// Render image layer with offset
void render_image_layer(Window *window, tmx_layer *layer, float offset_x, float offset_y) {
	if (!layer->content.image) return;
	SDL_Texture *tex = (SDL_Texture*)layer->content.image->resource_image;

	SDL_FRect dest = {
		.x = layer->offsetx + offset_x,
		.y = layer->offsety + offset_y,
		.w = (float)layer->content.image->width,
		.h = (float)layer->content.image->height
	};

	SDL_RenderTexture(window->renderer, tex, NULL, &dest);
}

// Render object layer with offset
void render_object_layer(Window *window, tmx_object_group *group, float offset_x, float offset_y) {
	tmx_object *obj = group->head;
	while (obj) {
		if (obj->visible && obj->obj_type == OT_SQUARE) {
			SDL_FRect rect = {
				.x = obj->x + offset_x,
				.y = obj->y + offset_y,
				.w = obj->width,
				.h = obj->height
			};
			SDL_RenderRect(window->renderer, &rect);
		}
		obj = obj->next;
	}
}

// Recursively render layers with offset
void render_layers(Window *window, tmx_map *map, tmx_layer *layer, float offset_x, float offset_y) {
	while (layer) {
		if (!layer->visible) {
			layer = layer->next;
			continue;
		}

		switch (layer->type) {
			case L_LAYER:
				render_tile_layer(window, map, layer, offset_x, offset_y);
				break;
			case L_IMAGE:
				render_image_layer(window, layer, offset_x, offset_y);
				break;
			case L_OBJGR:
				render_object_layer(window, layer->content.objgr, offset_x, offset_y);
				break;
			case L_GROUP:
				render_layers(window, map, layer->content.group_head, offset_x, offset_y);
				break;
		}
		layer = layer->next;
	}
}

// Render full map at a given offset
void render_tmx_map(Window *window, tmx_map *map, float offset_x, float offset_y) {
	render_layers(window, map, map->ly_head, offset_x, offset_y);
}

// Free map
void free_tmx_map(tmx_map *map) {
	tmx_map_free(map);
}
