#ifndef RENDER_H
#define RENDER_H
#define STB_IMAGE_IMPLEMENTATION

#include <SDL3/SDL.h>
#include "window.h"
#include <stb_image.h>
#include <stdio.h>

typedef struct Texture {
    SDL_Texture* Image;  /**< The SDL texture for rendering */
    float x;
    float y;

} Texture;

Texture load_texture(const char* file_path, int width, int height, Window* window);
void render_texture(Texture *texture, Window *window);

#endif // RENDER_H