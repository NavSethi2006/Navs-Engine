#include "render.h"


void set_texture(Texture *texture,int x, int y, int width, int height) {
    texture->x = x;
    texture->y = y;
    texture->width = width;
    texture->height = height;
}

void render_texture(Texture *texture, Window *window) {
    SDL_RenderTexture(window->renderer, texture->Image, NULL, NULL);
}

void render_texture_with_rect(Texture *texture, Window *window, SDL_FRect *frame) {
    SDL_FRect texture_rect = { (float)texture->x, (float)texture->y, (float)texture->width, (float)texture->height};
    SDL_RenderTexture(window->renderer, texture->Image, frame, &texture_rect);
}


Animation init_animation(SDL_FRect rectangle[], int frame_count, int switch_time) {
    Animation* animation;
    animation = malloc(sizeof(Animation));
    animation->rectangle = malloc(sizeof(SDL_FRect)* frame_count);

    for(int i = 0; i <= frame_count; i++) {
        animation->rectangle[i] = rectangle[i];
    }

    animation->switch_time = switch_time;
    animation->current_frame = 0;

}

void update_animation(Animation *animation) {  
    Uint32 time = SDL_GetTicks();
    if(time >= animation->switch_time) {
        time -= animation->switch_time;
        animation->current_frame++;
    }
    if (animation->current_frame >= animation->frame_count) {
        animation->current_frame = 0;
    }
}

void render_animation(Texture* texture, Animation *animation, Window *window) {
    
    render_texture_with_rect(texture, window, &animation->rectangle[animation->current_frame]);
}




