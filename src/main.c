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




    return 0;
}