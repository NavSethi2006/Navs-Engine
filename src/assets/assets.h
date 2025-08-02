#ifndef ASSETS_H
#define ASSETS_H

#include "../window.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL3/SDL_image.h>
#include <SDL3/SDL.h>
#include "../render.h"
#include "../tilemap.h"


typedef struct Asset_Texture {
    char *key;
    NE_Texture texture;
    struct Asset_Texture* next;
} Asset_Texture;

typedef struct Asset_Map {
    char *key;
    NE_TileMap *map;
    struct Asset_Map* next;
} Asset_Map;

void init_asset_manager(NE_Window* window);
NE_Texture get_texture_asset(const char* file_path);
void* map_texture_loader(const char *path);
NE_TileMap* get_map_asset(const char* file_path, int x, int y, bool draw_debug_for_obj_layer);
SDL_Renderer *get_renderer();

void free_all_assets();

#endif // ASSETS_H