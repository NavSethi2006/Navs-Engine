#ifndef TILEMAP_H
#define TILEMAP_H

#include "tmx/tmx.h"
#include "render.h"
#include <SDL3/SDL.h>
#include <stdio.h>
#include "window.h"
#include "assets/assets.h"

typedef struct TileMap {
    tmx_map *map;
    Texture *tileset;
    tmx_layer *layer;
    tmx_tile **tiles;
    bool Debug_lines;
    int x, y;
    int scale;
}TileMap;


TileMap* load_tmx_map(const char *path, int x, int y, int scale, bool draw_debug_for_obj_layer);
SDL_Color tmx_to_sdl_color(unsigned int color);
void* map_texture_loader(const char *path);
void draw_tile(Window *window, TileMap *map,tmx_tile *tile, int x, int y);
void render_tile_layer(Window *window, TileMap *map);
void render_object_layer(Window *window,TileMap *map, tmx_object_group *objgrp);
void render_layers(Window *window, TileMap *map, tmx_layer *layer);
void render_tmx_map(Window *window, TileMap *map);
void free_tmx_map(TileMap *map);

#endif