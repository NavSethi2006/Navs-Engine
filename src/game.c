#include "game.h"

Texture tex;
Animation animation1;
Animation animation2;

Animation animations[2];

enum PlayerStates {
    IDLE,
    RUN
} PlayerStates;


void game() {
    PlayerStates = IDLE;

    tex = get_texture_asset("../src/assets/player.png");
    set_texture(&tex, 0, 0, 20, 20);

    SDL_FRect animation_tex_coords1[3] = {{0, 33, 20, 31},
                               {20, 33, 20, 31},
                               {40, 33, 20, 31}};

    SDL_FRect animation_tex_coords2[1] = {0,0,17,32};


    animation1 = init_animation(animation_tex_coords1, 3, 0.1);

    animation2 = init_animation(animation_tex_coords2, 1, 0.1);



    animations[0] = animation1;
    animations[1] = animation2;


}


void game_handle_event(SDL_Event *event) {
    if(event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE) {
        switch_scene(get_menu_scene());
    }

    if(event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_RIGHT) {
        PlayerStates = RUN;
    }
    if(event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_DOWN) {
        PlayerStates = IDLE;
    }
}

void game_update() {
    


    switch (PlayerStates)
    {
    case IDLE:
        update_animation(&animations[0]);
        break;
    case RUN:
        update_animation(&animations[1]);
        break;
    default:
        break;
    }


}

void game_render(Window *window) {

    render_animation(&tex, animations, window);
    printf("nigga");



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
