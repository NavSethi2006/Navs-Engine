#ifndef RENDER_H
#define RENDER_H
#define STB_IMAGE_IMPLEMENTATION

#include <SDL3/SDL.h>
#include "window.h"
#include <stdio.h>

typedef struct Texture {
    SDL_Texture* Image;  /**< The SDL texture for rendering */
    int x;
    int y;
    int width;
    int height;
} Texture;


typedef struct Animation {
    SDL_FRect *rectangle;
    int frame_count;
    float switch_time;
    int current_frame;
} Animation;


void render_texture(Texture *texture, Window *window);
void set_texture(Texture *texture,int x, int y, int width, int height);
void render_texture_with_rect(Texture *texture, Window *window, SDL_FRect* frame);


Animation init_animation(SDL_FRect rectangle[], int frame_count, int switch_time);

void update_animation(Animation *animation);

void render_animation(Texture* texture, Animation *animation, Window *window);



#endif // RENDER_H