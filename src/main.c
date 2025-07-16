/*
 * 
 * 
 * 
 * 
 * 
 */

#include <SDL3/SDL.h>
#include <stdio.h>
#include "window.h"
#include "scene.h"
#include "game.h"




int init_all() {

    if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    if(SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize subsystems! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0) {
        printf("SDL could not initialize subsystems! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    if(SDL_InitSubSystem(SDL_INIT_CAMERA) < 0) {
        printf("SDL could not initialize subsystems! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    if(SDL_InitSubSystem(SDL_INIT_GAMEPAD) < 0) {
        printf("SDL could not initialize subsystems! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }
    if(SDL_InitSubSystem(SDL_INIT_HAPTIC) < 0) {
        printf("SDL could not initialize subsystems! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    return 0;

}


int main(int argc, char* argv[]) {
    
    init_all();

    Window window;
    SDL_Event event;

    create_window(&window, "Online Pong", 800, 600);

    switch_scene(get_game_scene());

    int gameloop = 1;

    while(gameloop) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                gameloop = 0;
            }


            if (CURRENT_SCENE && CURRENT_SCENE->handle_event) {
                CURRENT_SCENE->handle_event(&event);
            }

        }

        if (CURRENT_SCENE && CURRENT_SCENE->update) {
            CURRENT_SCENE->update();
        }

        begin_rendering(&window);

        if (CURRENT_SCENE && CURRENT_SCENE->render) {
            CURRENT_SCENE->render(&window);
        }

        end_rendering(&window);


        SDL_Delay(16);  // Roughly 60 FPS (1000ms / 60 ≈ 16.6ms)

    }



    return 0;
}