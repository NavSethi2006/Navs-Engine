#include <SDL3/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event e;
    int quit = 0;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    window = SDL_CreateWindow("window", 200, 200, 0);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Set renderer draw color to white
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Main loop
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_EVENT_QUIT) {
                quit = 1;
            }
        }

        // Clear screen
        SDL_RenderClear(renderer);

        // Update screen
        SDL_RenderPresent(renderer);
    }

    // Destroy renderer
    SDL_DestroyRenderer(renderer);
    // Destroy window
    SDL_DestroyWindow(window);
    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}