#ifndef TILEMAP_H
#define TILEMAP_H

#include "tmx/tmx.h"
#include "render.h"
#include <SDL3/SDL.h>
#include <stdio.h>
#include "window.h"



typedef struct TileMap {
    tmx_map map;
    tmx_layer layer;
    tmx_tileset tileset;
    tmx_image image;

} TileMap;

tmx_map *load_tilemap(const char* path);
void draw_polyline(Window *window,double **points, double x, double y, int pointsc);
void draw_polygon(Window *window, double **points, double x, double y, int pointsc);
void draw_objects(Window *window, tmx_object_group *objgr);
void draw_tile(Window *window,Texture *image, unsigned int sx, unsigned int sy, unsigned int sw, unsigned int sh,
               unsigned int dx, unsigned int dy, float opacity, unsigned int flags);

void draw_layer(Window *window,tmx_map *map, tmx_layer *layer);
void draw_image_layer(Window *window, Texture *texture);
void draw_all_layers(Window *window, tmx_map *map, tmx_layer *layers, Texture *texture);
void render_map(Window *window, tmx_map *map, Texture *texture);






#endif