/**
 * @file scene.h
 * @brief Scene management system for controlling game state transitions.
 */

 #ifndef SCENE_H
 #define SCENE_H
 
 #include <SDL3/SDL.h>
 #include "window.h"
 
 /**
  * @struct Scene
  * @brief A modular interface for game states/scenes.
  */
 typedef struct NE_Scene {
     void (*init)(void);                              /**< Called when the scene starts. */
     void (*handle_event)(SDL_Event *event);          /**< Handles input events. */
     void (*update)(float delta_time);                /**< Updates scene logic. */
     void (*render)(NE_Window *window);    
     void (*free) (void);              /**< Renders the scene to the screen. */
 } NE_Scene;
 
 /** Pointer to the currently active scene. */
 extern struct NE_Scene *CURRENT_SCENE;
 
/**
 * @brief Switch to a new scene.
 * @param new_scene Pointer to the Scene to switch to.
 */
void switch_scene(NE_Scene *new_scene);

/**
 * @brief Get the current active scene.
 * @return The current Scene structure (by value).
 */
NE_Scene get_current_scene();

/**
 * @brief Free any resources and clean up the given scene.
 * @param scene Pointer to the Scene to destroy.
 */
void destroy_scene(NE_Scene *scene);
 
 #endif // SCENE_H