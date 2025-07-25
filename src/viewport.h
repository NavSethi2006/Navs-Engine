/**
 * @file viewport.h
 * @brief Handles camera position, zoom, and world-to-screen conversion.
 */

 #ifndef VIEWPORT_H
 #define VIEWPORT_H
 
 #include <SDL3/SDL.h>
 #include "window.h"
 
 /**
  * @struct Viewport
  * @brief Represents a 2D camera in world space.
  */
 typedef struct Viewport {
     float x, y;         /**< Camera top-left position in world space. */
     int width, height;  /**< Screen-space dimensions in pixels. */
     float zoom;         /**< Zoom level (1.0 = normal, 2.0 = zoomed in). */
 } Viewport;
 
 /**
 * @brief Initialize a new viewport (camera).
 * @param x Initial world x-position.
 * @param y Initial world y-position.
 * @param width Width of the viewport in screen pixels.
 * @param height Height of the viewport in screen pixels.
 * @param zoom Zoom level (1.0 = no zoom).
 * @return Pointer to the created Viewport.
 */
Viewport* viewport_init(float x, float y, int width, int height, float zoom);

/**
 * @brief Move the viewport camera to a new world-space position.
 * @param vp Pointer to the Viewport to move.
 * @param destination_x Target world x-coordinate.
 * @param destination_y Target world y-coordinate.
 */
void viewport_move(Viewport *vp, float destination_x, float destination_y);

/**
 * @brief Get the current world-space bounds visible through the viewport.
 * @param vp Pointer to the Viewport.
 * @return A rectangle representing the visible area in world space.
 */
SDL_FRect viewport_get_view(Viewport *vp);

/**
 * @brief Convert a rectangle from world-space to screen-space.
 * @param vp Pointer to the Viewport.
 * @param world_rect The rectangle in world coordinates.
 * @return A new rectangle transformed into screen coordinates.
 */
SDL_FRect viewport_world_to_screen(Viewport *vp, SDL_FRect world_rect);

/**
 * @brief Determine whether a world-space rectangle is outside the camera's view.
 * @param vp Pointer to the Viewport.
 * @param world_rect Rectangle in world space to test.
 * @return true if the rectangle is outside the viewport; false if visible.
 */
bool camera_cull_rect(Viewport *vp, SDL_FRect world_rect);
 
 #endif