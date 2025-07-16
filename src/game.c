#include "game.h"


void game() {
    printf("game init\n");
}

void game_handle_event(SDL_Event *event) {
    printf("game handle event\n");
    if(event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE) {
        switch_scene(get_menu_scene());
    }
}

void game_update() {
    printf("game update\n");
}

void game_render(Window *window) {
    printf("game render\n");
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
