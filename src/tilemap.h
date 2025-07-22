#ifndef TILEMAP_H
#define TILEMAP_H

#include "tmx/tmx.h"
#include "render.h"
#include <SDL3/SDL.h>
#include <stdio.h>
#include "window.h"
#include "assets/assets.h"


tmx_map* load_tmx_map(const char *path);
SDL_Color tmx_to_sdl_color(unsigned int color);
void* map_texture_loader(const char *path);
void draw_tile(Window *window, tmx_tile *tile, int x, int y, float offset_x, float offset_y);
void render_tile_layer(Window *window, tmx_map *map, tmx_layer *layer, float offset_x, float offset_y);
void render_object_layer(Window *window, tmx_object_group *group, float offset_x, float offset_y);
void render_layers(Window *window, tmx_map *map, tmx_layer *layer, float offset_x, float offset_y);
void render_tmx_map(Window *window, tmx_map *map, float offset_x, float offset_y);
void free_tmx_map(tmx_map *map);

#endif