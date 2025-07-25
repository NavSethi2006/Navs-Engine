
#include "scene.h"


Scene *CURRENT_SCENE = NULL;


void switch_scene(Scene *new_scene) {
    CURRENT_SCENE = new_scene;
    if (CURRENT_SCENE && CURRENT_SCENE->init) {
        CURRENT_SCENE->init();
    }
}

Scene get_current_scene() {

    if (CURRENT_SCENE) {
        return *CURRENT_SCENE;
    } else {
        Scene empty_scene = {0};
        return empty_scene; // Return an empty scene if none is set
    }
}

void destroy_scene(Scene *scene) {
    scene->init = NULL;
    scene->handle_event = NULL;
    scene->update = NULL;
    scene->render = NULL;
    
    free(scene);
    scene = NULL; // Set to NULL to avoid dangling pointer
}
