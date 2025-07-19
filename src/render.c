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

void render_texture_with_rect(Texture *texture, Window *window, Frame *frame) {
    SDL_FRect texture_rect = { (float)texture->x, (float)texture->y, (float)texture->width, (float)texture->height};
    SDL_FRect dst_rect = { (float)frame->x, (float)frame->y, (float)frame->width, (float)frame->height };

    if(SDL_RenderTexture(window->renderer, texture->Image, &dst_rect, &texture_rect)) {
        printf("Rendering successfully: %s\n", SDL_GetError());
    }else {
        printf("Error Rendering: %s\n", SDL_GetError());
    }
}


Animation* init_animation(Frame *frames,int frame_count, float switch_time) {
    Animation *animation = malloc(sizeof(Animation));
    animation->switch_time = switch_time;
    animation->frame_count = frame_count;
    animation->frames = malloc(sizeof(Frame) * frame_count);
    animation->current_frame = 0;
    animation->timer = 0.0f;

    for (int i = 0; i < frame_count; i++) {
        animation->frames[i] = frames[i];
    }
    return animation;
}

void update_animation(Animation *animation, float delta_time) {
    animation->timer += delta_time;
    if (animation->timer >= animation->switch_time) {
        animation->timer = 0.0f;
        animation->current_frame = (animation->current_frame + 1) % animation->frame_count;
    }
}

void render_animation(Animation *animation, Window *window, Texture *texture) {   
    Frame *frame = &animation->frames[animation->current_frame];
    render_texture_with_rect(texture, window, frame);
}

void update_animation_set(Animation_set *animations, int current_state,float delta_time) {
    update_animation(animations->animations[current_state], delta_time);
}

void render_animation_set(Animation_set *animations, int current_state,Window *window) {
    render_animation(animations->animations[current_state], window, animations->texture);
}


