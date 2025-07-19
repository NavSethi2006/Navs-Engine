#ifndef RENDER_H
#define RENDER_H
#define STB_IMAGE_IMPLEMENTATION

#include <SDL3/SDL.h>
#include "window.h"
#include <stdio.h>


typedef enum {
    ANIM_IDLE,
    ANIM_RUN,
    ANIM_JUMP,
    ANIM_ATTACK,
    ANIM_HURT,
    ANIM_DEATH,
    ANIM_WALK,
    ANIM_FALL,
    ANIM_CROUCH,
    ANIM_CLIMB,
    ANIM_SWIM,
    ANIM_RESPAWN,
    ANIM_COUNT
} AnimationState;

typedef struct Texture {
    SDL_Texture* Image;  /**< The SDL texture for rendering */
    int x;
    int y;
    int width;
    int height;
} Texture;

typedef struct Frame {
    float x;
    float y;
    float width;
    float height;
} Frame;

typedef struct Animation {
    Frame *frames;
    int frame_count;
    float switch_time;
    int current_frame;
    float timer;
} Animation;

typedef struct Animation_set {
    Texture *texture;
    AnimationState current_state;
    Animation *animations[];
} Animation_set;


void render_texture(Texture *texture, Window *window);
void set_texture(Texture *texture,int x, int y, int width, int height);
void render_texture_with_rect(Texture *texture, Window *window, Frame* frame);


Animation* init_animation(Frame *frames,int frame_count, float switch_time);

void update_animation(Animation *animation, float delta_time);
void render_animation(Animation *animation, Window *window, Texture *texture);

void update_animation_set(Animation_set *animations, int current_state,float delta_time);
void render_animation_set(Animation_set *animations, int current_state,Window *window);



#endif // RENDER_H