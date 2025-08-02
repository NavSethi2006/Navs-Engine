#include "render.h"

static NE_Viewport *viewport_rect;

void set_render_viewport(NE_Viewport *vp) {
    viewport_rect = vp;
}

void set_texture(NE_Texture *texture,int x, int y, int width, int height) {
    texture->x = x;
    texture->y = y;
    texture->width = width;
    texture->height = height;
}

void render_texture(NE_Texture *texture, NE_Window *window) {
    SDL_RenderTexture(window->renderer, texture->Image, NULL, NULL);
}

void render_texture_with_rect(NE_Texture *texture, NE_Window *window, NE_Frame *frame) {

    SDL_FRect texture_rect = { ((float)texture->x - viewport_rect->x) * viewport_rect->zoom, 
                                ((float)texture->y - viewport_rect->y) * viewport_rect->zoom, 
                                (float)texture->width * viewport_rect->zoom, 
                                (float)texture->height * viewport_rect->zoom};
    SDL_FRect dst_rect = { (float)frame->x, (float)frame->y, (float)frame->width, (float)frame->height };

    SDL_RenderTexture(window->renderer, texture->Image, &dst_rect, &texture_rect);
 
}


void render_with_size_and_rect(NE_Texture *texture, NE_Window *window, SDL_FRect *srcrect, SDL_FRect *dstrect ) {
    SDL_FRect newrect = {(dstrect->x - viewport_rect->x) * viewport_rect->zoom,
                (dstrect->y - viewport_rect->y) * viewport_rect->zoom,
                dstrect->w * viewport_rect->zoom,
                dstrect->h * viewport_rect->zoom
            };

    SDL_RenderTexture(window->renderer, texture->Image, srcrect, &newrect);
}

NE_Animation_set* init_animation_set(NE_Texture *texture,int animation_count, float x, float y, float width, float height) {
    NE_Animation_set *animations = malloc(sizeof(NE_Animation_set));
    texture->x = x;
    texture->y = y;
    texture->width = width;
    texture->height = height;
    animations->texture = texture;
    animations->animation_count = animation_count;

    return animations;
}


NE_Animation* init_animation(NE_Frame *frames,int frame_count, float switch_time) {
    NE_Animation *animation = malloc(sizeof(NE_Animation));
    animation->switch_time = switch_time;
    animation->frame_count = frame_count;
    animation->frames = malloc(sizeof(NE_Frame) * frame_count);
    animation->current_frame = 0;
    animation->timer = 0.0f;

    for (int i = 0; i < frame_count; i++) {
        animation->frames[i] = frames[i];
    }

    return animation;
}

void update_animation(NE_Animation *animation, float delta_time) {

    animation->timer += delta_time;

    if (animation->timer >= animation->switch_time) {
        animation->timer = 0.0f;
        animation->current_frame = (animation->current_frame + 1) % animation->frame_count;
    }
}

void render_animation(NE_Animation *animation, NE_Window *window, NE_Texture *texture) {   
    NE_Frame *frame = &animation->frames[animation->current_frame];   
    SDL_FRect dest = { (texture->x - viewport_rect->x) * viewport_rect->zoom, 
                        (texture->y - viewport_rect->y) * viewport_rect->zoom,
                        texture->width * viewport_rect->zoom,
                        texture->height * viewport_rect->zoom };
    SDL_FRect src = { frame->x, frame->y, frame->width, frame->height };

    SDL_RenderTexture(window->renderer, texture->Image, &src, &dest);
}

void update_animation_set(NE_Animation_set *animations, int current_state,float delta_time) {
    update_animation(animations->animations[current_state], delta_time);
}

void render_animation_set(NE_Animation_set *animations, int current_state,NE_Window *window) {
    render_animation(animations->animations[current_state], window, animations->texture);
}

void free_animation(NE_Animation *animation) {
    if (animation) {
        free(animation->frames);
        animation->frames = NULL;
        free(animation);
        animation = NULL;
    }
}

void free_animation_set(NE_Animation_set *animation) {
    if (animation) {
        for (int i = 0; i < animation->animation_count; i++) {
            free_animation(animation->animations[i]);
        }
        free(animation->texture);
        animation->texture = NULL;
        free(animation);
        animation = NULL;
    }
}




