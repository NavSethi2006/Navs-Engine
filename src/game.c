#include "game.h"

Texture tex;
Animation *animation;

Frame animation_tex_coords1[3] = {{0, 33, 20, 31},
                               {20, 33, 20, 31},
                               {40, 33, 20, 31}};

Frame animation_tex_coords2[1] = {0,0,17,32};


enum PlayerStates {
    IDLE,
    RUN
} PlayerStates;


void game() {
    PlayerStates = IDLE;

    tex = get_texture_asset("../src/assets/player.png");
    set_texture(&tex, 20, 20, 200, 300);

    animation = init_animation(animation_tex_coords1, 3, 0.1);

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

void game_update(float delta_time) {

    switch (PlayerStates)
    {
    case IDLE:
        update_animation(animation, delta_time);
        break;
    case RUN:
        update_animation(animation, delta_time);
        break;
    default:
        break;
    }


}

void game_render(Window *window) {

//    render_animation(animation, window, &tex);

    render_texture_with_rect(&tex, window, &animation_tex_coords2[0]); // Render the second texture with different coordinates

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
