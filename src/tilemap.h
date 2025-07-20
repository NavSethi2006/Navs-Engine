#ifndef TILEMAP_H
#define TILEMAP_H

#include <SDL3/SDL.h>
#include "window.h"
#include "render.h"

#define TILE_SIZE 32
#define MAX_TILES_X 100
#define MAX_TILES_Y 100

typedef struct Tile {
    int id;
    SDL_FRect src; // Position in the tile atlas
} Tile;

typedef struct TileMap {
    Tile tiles[MAX_TILES_Y][MAX_TILES_X];
    int width, height;
    Texture* atlas;
} TileMap;

void init_tilemap(TileMap* map, Texture *atlas, int width, int height);
void draw_tilemap(TileMap* map, Window* window);
void set_tile(TileMap* map, int x, int y, int tile_id);

#endif