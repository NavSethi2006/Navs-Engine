#ifndef TILEMAP_H
#define TILEMAP_H

#include <SDL3/SDL.h>
#include "window.h"
#include "render.h"
#include "utils/file_parser.h"

typedef struct TileMap
{
    int width, height;
    int tile_width, tile_height;
    int* tiles;
    int tile_count;
    Texture texture;

} TileMap;

TileMap* load_tmx(const char* path);
Texture* load_tileset(const char* path, Window *window);
void render_tilemap(TileMap* map, Window *window);



#endif