#include "tilemap.h"

tmx_map *load_tilemap(const char* path) {
    return tmx_load(path);
}



void draw_polyline(Window *window, double **points, double x, double y, int pointsc) {
    int i;
    for(i=1; 1 < pointsc; i++) {
        SDL_RenderLine(window->renderer,x+points[0][0], y+points[0][1], x+points[pointsc-1][0], y+points[pointsc-1][1]);
    }
}

void draw_polygon(Window *window,double **points, double x, double y, int pointsc) {
    draw_polyline(window,points, x, y, pointsc);
	if (pointsc > 2) {
		SDL_RenderLine(window->renderer, x+points[0][0], y+points[0][1], x+points[pointsc-1][0], y+points[pointsc-1][1]);
	}
}

void draw_objects(Window *window,tmx_object_group *objgr) {
    SDL_FRect rect;
	tmx_object *head = objgr->head;
	while (head) {
		if (head->visible) {
			if (head->obj_type == OT_SQUARE) {
				rect.x =     head->x;  rect.y =      head->y;
				rect.w = head->width;  rect.h = head->height;
				SDL_RenderRect(window->renderer, &rect);
			}
			else if (head->obj_type  == OT_POLYGON) {
				draw_polygon(window ,head->content.shape->points, head->x, head->y, head->content.shape->points_len);
			}
			else if (head->obj_type == OT_POLYLINE) {
				draw_polyline(window ,head->content.shape->points, head->x, head->y, head->content.shape->points_len);
			}
			else if (head->obj_type == OT_ELLIPSE) {
				/* FIXME: no function in SDL2 */
			}
		}
		head = head->next;
	}
}

void draw_tile(Window *window,Texture *image, unsigned int sx, unsigned int sy, unsigned int sw, unsigned int sh,
               unsigned int dx, unsigned int dy, float opacity, unsigned int flags) {
    SDL_Rect src_rect, dest_rect;
	src_rect.x = sx;
	src_rect.y = sy;
	src_rect.w = dest_rect.w = sw;
	src_rect.h = dest_rect.h = sh;
	dest_rect.x = dx;
	dest_rect.y = dy;
	SDL_RenderTexture(window->renderer, image->Image, (SDL_FRect*)&src_rect, (SDL_FRect*)&dest_rect);

}

void draw_layer(Window *window,tmx_map *map, tmx_layer *layer) {
	unsigned long i, j;
	unsigned int gid, x, y, w, h, flags;
	float op;
	tmx_tileset *ts;
	tmx_image *im;
	void* image;
	op = layer->opacity;
	for (i=0; i<map->height; i++) {
		for (j=0; j<map->width; j++) {
			gid = (layer->content.gids[(i*map->width)+j]) & TMX_FLIP_BITS_REMOVAL;
			if (map->tiles[gid] != NULL) {
				ts = map->tiles[gid]->tileset;
				im = map->tiles[gid]->image;
				x  = map->tiles[gid]->ul_x;
				y  = map->tiles[gid]->ul_y;
				w  = ts->tile_width;
				h  = ts->tile_height;
				if (im) {
					image = im->resource_image;
				}
				else {
					image = ts->image->resource_image;
				}
				flags = (layer->content.gids[(i*map->width)+j]) & ~TMX_FLIP_BITS_REMOVAL;
				draw_tile(window ,image, x, y, w, h, j*ts->tile_width, i*ts->tile_height, op, flags);
			}
		}
	}
}


void draw_image_layer(Window *window,Texture *texture) {
	SDL_Rect dim;
	dim.x = dim.y = 0;

	render_texture(texture, window);
}

void draw_all_layers(Window *window, tmx_map *map, tmx_layer *layers, Texture *texture) {
	while (layers) {
		if (layers->visible) {

			if (layers->type == L_GROUP) {
				draw_all_layers(window ,map, layers->content.group_head, texture);
			}
			else if (layers->type == L_OBJGR) {
				draw_objects(window,layers->content.objgr);
			}
			else if (layers->type == L_IMAGE) {
				draw_image_layer(window, texture);
			}
			else if (layers->type == L_LAYER) {
				draw_layer(window ,map, layers);
			}
		}
		layers = layers->next;
	}
}

void render_map(Window* window,tmx_map *map, Texture *background) {
    draw_all_layers(window, map, map->ly_head, background);
}


