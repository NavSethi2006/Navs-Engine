#include <SDL3/SDL.h>
#include <stdio.h>


typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width, height;
} Window;

void create_window(Window *window, const char* title,int width, int height);
void fullscreen_window(Window *window);
void borderless_window(Window *window);
void windowed_window(Window *window);
void add_flag_window(Window *window, SDL_WindowFlags flag);
bool is_fullscreen(Window *window);
void destroy_window(Window *window);

