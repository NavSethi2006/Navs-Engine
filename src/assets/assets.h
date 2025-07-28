#ifndef ASSETS_H
#define ASSETS_H

#include "../window.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <SDL3/SDL_image.h>
#include <SDL3/SDL.h>

 /**
  * @struct Texture
  * @brief Represents a drawable image and its size/position in world space.
  */
 typedef struct Texture {
    SDL_Texture* Image; /**< SDL texture image. */
    float x, y;          /**< World-space position. */
    float width, height; /**< World-space dimensions. */
} Texture;

typedef struct Asset_Texture {
    char *key;
    Texture texture;
    struct Asset_Texture* next;
} Asset_Texture;

typedef struct Asset_Map {
    char *key;
    struct Asset_Map* next;
} Asset_Map;

void init_asset_manager(Window* window);
Texture get_texture_asset(const char* file_path);
SDL_Renderer *get_renderer();

void free_all_assets();

#endif // ASSETS_H