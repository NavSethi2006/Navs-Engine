#ifndef SCENE_H
#define SCENE_H

#include <SDL3/SDL.h>
#include <stdio.h>


typedef struct Scene {
    void (*init)(void);
    void (*handle_event)(SDL_Event *event);
    void (*update)(void);
    void (*render)(void);
} Scene;
 

void switch_scene(Scene *new_scene);
Scene get_current_scene();
void destroy_scene(Scene *scene);

#endif // SCENE_H

