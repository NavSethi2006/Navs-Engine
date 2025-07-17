#ifndef RENDER_H
#define RENDER_H
#define STB_IMAGE_IMPLEMENTATION

#include <SDL3/SDL.h>
#include "window.h"
#include <stdio.h>

typedef struct Texture {
    SDL_Texture* Image;  /**< The SDL texture for rendering */
    float x;
    float y;
    float width;
    float height;
} Texture;

typedef struct Animation {
    Texture texture;
    SDL_FRect* frames;
    int frame_count;
    float switch_time;
} Animation;

void render_texture(Texture *texture, Window *window);



#endif // RENDER_H