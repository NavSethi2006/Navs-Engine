#include "game.h"

Texture tex;
Texture tileset;
Animation_set *animations;
Animation *animation;
TileMap *tilemap;
Texture background;
Viewport *vp;
SDL_Rect rect;

Frame RUN_ANIMATION[3] = {{0, 33, 20, 31},
                               {20, 33, 20, 31},
                               {40, 33, 20, 31}};

Frame IDLE_ANIMATION[1] = {0,0,17,32};

Frame JUMP_ANIMATION[5] = {{40, 80, 18, 31},
                               {70, 83, 16, 25},
                               {97, 86, 23, 20},
                               {129, 83, 18, 25},
                               {157, 84, 22, 23}};
                               
Frame WALL_CLIMB_ANIMATION[4] = {{0,199,17,32},
                                {40,201,17,32},
                                {80,200,16,31},
                            {118, 201, 23,31}};

Frame ATTACK_ANIMATION[4] = {{0,240,17,30},
                            {28,241,42,30},
                            {74,241,29,30},
                            {115,241,27,29}};

enum PlayerStates {
    IDLE,
    RUN,
    JUMP,
    WALL_CLIMB,
    ATTACK

} PlayerStates;



void game() {

    vp = viewport_init(500, 0, 1600, 800, 3);

    set_render_viewport(vp);

    tex = get_texture_asset("../src/assets/player.png");

    set_texture(&tex, 20, 20, 30, 55);

    animations = malloc(sizeof(Animation_set));
    animations->animations[IDLE] = init_animation(IDLE_ANIMATION, 1, 0.2f);
    animations->animations[RUN] = init_animation(RUN_ANIMATION, 3, 0.2f);
    animations->animations[JUMP] = init_animation(JUMP_ANIMATION, 5, 0.1f);
    animations->animations[ATTACK] = init_animation(ATTACK_ANIMATION, 4, 0.1f);
    animations->animations[WALL_CLIMB] = init_animation(WALL_CLIMB_ANIMATION, 4, 0.1f);
    animations->texture = &tex;
    PlayerStates = IDLE;

    tmx_img_load_func = (void*(*)(const char*))map_texture_loader;
    tmx_img_free_func = (void (*)(void*))SDL_DestroyTexture;

    tilemap = load_tmx_map("../src/assets/untitled.tmx",0, 0, false);   

}


void game_handle_event(SDL_Event *event) {

    if(event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE) {
        switch_scene(get_menu_scene());
    }

    if(event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_W) {
        PlayerStates = RUN;
        viewport_move(vp, 0, -20);


    }
    if(event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_S) {
        PlayerStates = IDLE;
        viewport_move(vp, 0, 20);

    }
    if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_SPACE) {
        PlayerStates = JUMP;
    }
    if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_A) {
        PlayerStates = ATTACK;
        viewport_move(vp, -20, 0);


    }
    if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_D) {
        PlayerStates = WALL_CLIMB;
        viewport_move(vp, 20, 0);
    }


}

void game_update(float delta_time) {

    update_animation_set(animations, PlayerStates, delta_time);

}

void game_render(Window *window) {
    
    render_tmx_map(window, tilemap);
    
    render_animation_set(animations, PlayerStates, window);

    vp->x -= 10;
}

void free_game() {
    free_tmx_map(tilemap);
}


Scene Game_Scene = {
    .init  = game,
    .handle_event = game_handle_event,
    .update = game_update,
    .render = game_render
};

Scene *get_game_scene() {
    return &Game_Scene;
}
