#ifndef RENDER_H
#define RENDER_H

#include <SDL3/SDL.h>
#include "window.h"
#include <stdio.h>

typedef struct Texture {
    SDL_Texture* Image;  /**< The SDL texture for rendering */
    float x;
    float y;
    float width;                 /**< Width of the texture */
    float height;                /**< Height of the texture */

} Texture;

Texture load_texture(const char* file_path, int x, int y, int width, int height);
void render_texture(Texture *texture, Window *window);

#endif // RENDER_H