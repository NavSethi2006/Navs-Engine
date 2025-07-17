#include "window.h"

void create_window(Window *window, const char* title,int width, int height) {
    window->width = width;
    window->height = height;

    // Create window
    window->window = SDL_CreateWindow(title, width, height, 0);
    if (window->window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    // Create renderer
    window->renderer = SDL_CreateRenderer(window->window, NULL);
    if (window->renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window->window);
        return;
    }

    // Set renderer draw color to white
}


void begin_rendering(Window *window) {
    SDL_SetRenderDrawColor(window->renderer, 0, 0, 0, 255);
    SDL_RenderClear(window->renderer);
}


void end_rendering(Window *window) {
    SDL_RenderPresent(window->renderer);
}


void fullscreen_window(Window *window){ SDL_SetWindowFullscreen(window->window, true); }
void borderless_window(Window *window){ SDL_SetWindowBordered(window->window, true); }
void windowed_window(Window *window) { SDL_SetWindowFullscreen(window->window, false); }

bool is_fullscreen(Window *window) {
    return SDL_GetWindowFlags(window->window) & SDL_WINDOW_FULLSCREEN;
}

void destroy_window(Window *window) {
    if (window->renderer) {
        SDL_DestroyRenderer(window->renderer);
    }
    if (window->window) {
        SDL_DestroyWindow(window->window);
    }
    window->renderer = NULL;
    window->window = NULL;
    window->width = 0;
    window->height = 0;

    free(window);
}