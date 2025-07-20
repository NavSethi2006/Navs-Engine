#include "menu.h"


void menu() {
}

void menu_handle_event(SDL_Event *event) {
    if(event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE) {
        switch_scene(get_game_scene());
    }
}

void menu_update(float delta_time) {
}

void menu_render(Window* window) {
    
}

Scene Menu_Scene = {
    .init  = menu,
    .handle_event = menu_handle_event,
    .update = menu_update,
    .render = menu_render
};

Scene *get_menu_scene() {
    return &Menu_Scene;
}

