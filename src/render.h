/**
 * @file render.h
 * @brief Rendering system for textures, animations, and viewports.
 */

 #ifndef RENDER_H
 #define RENDER_H
 
 #include <SDL3/SDL.h>
 #include "window.h"
 #include "viewport.h"
 #include "assets/assets.h"
 

 
 /**
  * @struct Frame
  * @brief Represents a rectangular frame of an animation.
  */
 typedef struct Frame {
     float x, y;          /**< Top-left position in the texture. */
     float width, height; /**< Size of the frame. */
 } Frame;
 
 /**
  * @struct Animation
  * @brief Holds a sequence of frames and controls animation timing.
  */
 typedef struct Animation {
     Frame *frames;       /**< Array of frames. */
     int frame_count;     /**< Number of frames. */
     float switch_time;   /**< Time between frame switches (in seconds). */
     int current_frame;   /**< Currently displayed frame index. */
     float timer;         /**< Timer tracking elapsed time. */
 } Animation;
 
 /**
  * @struct Animation_set
  * @brief A collection of animations tied to a shared texture.
  */
 typedef struct Animation_set {
     Texture *texture;    /**< The texture shared across animations. */
     int animation_count; /** < The count of animations. */
     Animation *animations[]; /**< Array of animations for different states. */
 } Animation_set;
 
/**
 * @brief Set the SDL rendering viewport to a given Viewport.
 *  THIS MUST BE SET BEFORE YOUR RENDER ANYTHING
 * @param vp Pointer to the Viewport to set as active.
 */
void set_render_viewport(Viewport *vp);

/**
 * @brief Render a full texture to the screen using its world position and size.
 * @param texture Pointer to the texture to render.
 * @param window Pointer to the Window containing the renderer.
 */
void render_texture(Texture *texture, Window *window);

/**
 * @brief Set the properties of a texture's position and size.
 * @param texture Pointer to the texture to modify.
 * @param x World-space x-coordinate.
 * @param y World-space y-coordinate.
 * @param width Width of the texture in world units.
 * @param height Height of the texture in world units.
 */
void set_texture(Texture *texture, int x, int y, int width, int height);

/**
 * @brief Render a specific frame of a texture.
 * @param texture Pointer to the texture to render.
 * @param window Pointer to the Window with the renderer.
 * @param frame Pointer to the frame data (source rectangle).
 */
void render_texture_with_rect(Texture *texture, Window *window, Frame* frame);

/**
 * @brief Render a portion of a texture to a destination on screen.
 * @param texture Pointer to the texture to render.
 * @param window Pointer to the Window to render to.
 * @param srcrect Source rectangle on the texture.
 * @param dstrect Destination rectangle on the screen.
 */
void render_with_size_and_rect(Texture *texture, Window *window, SDL_FRect *srcrect, SDL_FRect *dstrect);

/**
 * @brief Initialize an animation set with a specified number of animations.
 * @param texture Pointer to loaded texture.
 * @param animation_count Number of animations in the set.
 * @param x x coordinate for this animation set
 * @param y y coordinate for this animation set
 * @param width width of the animation set
 * @param height height of the animation set
 * @return Pointer to the newly created Animation_set.
 */
Animation_set* init_animation_set(Texture *texture, int animation_count, float x, float y, float width, float height);

/**
 * @brief Initialize an animation with a set of frames.
 * @param frames Pointer to array of Frame structs.
 * @param frame_count Number of frames in the array.
 * @param switch_time Time between frame switches, in seconds.
 * @return Pointer to the newly created Animation.
 */
Animation* init_animation(Frame *frames, int frame_count, float switch_time);

/**
 * @brief Update the current frame of an animation based on delta time.
 * @param animation Pointer to the Animation to update.
 * @param delta_time Time elapsed since last update, in seconds.
 */
void update_animation(Animation *animation, float delta_time);

/**
 * @brief Render the current frame of an animation using a texture.
 * @param animation Pointer to the Animation to render.
 * @param window Pointer to the Window used for rendering.
 * @param texture Pointer to the texture used for the animation.
 */
void render_animation(Animation *animation, Window *window, Texture *texture);

/**
 * @brief Update the active animation in an animation set based on state.
 * @param animations Pointer to the Animation_set to update.
 * @param current_state Index of the currently active animation.
 * @param delta_time Time elapsed since last update, in seconds.
 */
void update_animation_set(Animation_set *animations, int current_state, float delta_time);

/**
 * @brief Render the active animation from an animation set.
 * @param animations Pointer to the Animation_set to render.
 * @param current_state Index of the current animation state.
 * @param window Pointer to the Window for rendering.
 */
void render_animation_set(Animation_set *animations, int current_state, Window *window);

 
/**
 * @brief Free the memory allocated for an Animation.
 * @param animation pointer to the animation to free.
 * 
 */
void free_animation(Animation *animation);

 #endif // RENDER_H
 