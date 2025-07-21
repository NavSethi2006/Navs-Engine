#ifndef TILEMAP_H
#define TILEMAP_H

#include "assets/assets.h"
#include <SDL3/SDL.h>
#include "window.h"
#include "render.h"
#include "utils/file_parser.h"



#define FLIPPED_HORIZONTALLY 0x80000000
#define FLIPPED_VERTICALLY   0x40000000
#define FLIPPED_DIAGONALLY   0x20000000
#define GID_MASK             0x1FFFFFFF


typedef struct TileLayer {
    int id;
    char name[64];
    int width, height;
    float opacity;
    int visible;
    int* tiles;
} TileLayer;

typedef struct Tileset {
    int firstgid;
    int tile_width, tile_height;
    int columns, tilecount;
    int image_width, image_height;

    Texture* texture;

} Tileset;

typedef struct MapObject {
    char name[64];
    int id;
    float x,y,width,height;
} MapObject;

typedef struct ObjectLayer {
    char name[64];
    int id;
    int object_count;
    MapObject objects[];

} ObjectLayer;

typedef struct TileMap
{
    int width, height;
    int tile_width, tile_height;
    Texture texture;
    int layer_count;
    Tileset tileset;
    ObjectLayer object_layers[8];
    int object_layer_count;
    TileLayer layers[];
    

} TileMap;




TileMap* load_tmx(const char* path);
void load_tileset_into_map(TileMap *map, const char* xml);
void render_tilemap(Window *window, TileMap *map);
void free_tilemap(TileMap* map);


#endif