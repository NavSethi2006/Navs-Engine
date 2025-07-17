#include "game.h"

Texture tex;

void game() {
    tex = get_texture_asset("../src/assets/test.png");

}

void game_handle_event(SDL_Event *event) {
    if(event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE) {
        switch_scene(get_menu_scene());
    }
}

void game_update() {

}

void game_render(Window *window) {
    printf("game render\n");
    render_texture(&tex, window);
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
