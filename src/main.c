#include <SDL3/SDL.h>
#include <stdio.h>
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

    game(&window);

    int gameloop = 1;

    while(gameloop) {

        while (SDL_PollEvent(&event)) {w
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }

            // You can handle other events here too
        }

        // Rendering
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
        SDL_RenderClear(renderer);

        // Draw your stuff here...

        SDL_RenderPresent(renderer);

        SDL_Delay(16);  // Roughly 60 FPS (1000ms / 60 ≈ 16.6ms)

    }



    return 0;
}