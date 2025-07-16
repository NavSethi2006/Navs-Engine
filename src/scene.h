#ifndef SCENE_H
#define SCENE_H

#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "window.h"


typedef struct Scene {
    void (*init)(void);
    void (*handle_event)(SDL_Event *event);
    void (*update)(void);
    void (*render)(Window *window);
} Scene;
 
extern struct Scene *CURRENT_SCENE;

void switch_scene(Scene *new_scene);
Scene get_current_scene();
void destroy_scene(Scene *scene);

#endif // SCENE_H

