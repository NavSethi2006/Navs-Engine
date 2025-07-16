#ifndef WINDOW_H
#define WINDOW_H

#include <SDL3/SDL.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @struct Window
 * @brief Encapsulates the SDL window and renderer along with window dimensions.
 *
 * This struct holds the SDL_Window and SDL_Renderer pointers along with
 * the width and height of the window. It is used to manage rendering contexts.
 */
typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width, height;
} Window;
/**
 * @brief Creates and initializes a window and renderer.
 *
 * @param window Pointer to a Window struct to be initialized.
 * @param title Title of the window.
 * @param width Desired width of the window.
 * @param height Desired height of the window.
 */
void create_window(Window *window, const char* title, int width, int height);

/**
 * @brief Prepares the window for rendering by clearing the screen.
 *
 * @param window Pointer to the Window to begin rendering on.
 */
void begin_rendering(Window *window);

/**
 * @brief Presents the rendered content to the screen.
 *
 * @param window Pointer to the Window to end rendering on.
 */
void end_rendering(Window *window);

/**
 * @brief Sets the window to fullscreen mode.
 *
 * @param window Pointer to the Window to modify.
 */
void fullscreen_window(Window *window);

/**
 * @brief Sets the window to borderless fullscreen mode.
 *
 * @param window Pointer to the Window to modify.
 */
void borderless_window(Window *window);

/**
 * @brief Sets the window to windowed mode (resizable with borders).
 *
 * @param window Pointer to the Window to modify.
 */
void windowed_window(Window *window);

/**
 * @brief Checks whether the window is currently in fullscreen mode.
 *
 * @param window Pointer to the Window to check.
 * @return true if the window is in fullscreen mode, false otherwise.
 */
bool is_fullscreen(Window *window);

/**
 * @brief Destroys the window and renderer and cleans up resources.
 *
 * @param window Pointer to the Window to destroy.
 */
void destroy_window(Window *window);


#endif // WINDOW_H