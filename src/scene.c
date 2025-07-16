
#include "scene.h"


static Scene *current_scene = NULL;


void switch_scene(Scene *new_scene) {
    static Scene *current_scene = NULL;

    current_scene = new_scene;

    if (current_scene && current_scene->init) {
        current_scene->init();
    }

}

Scene get_current_scene() {
    static Scene *current_scene = NULL;

    if (current_scene) {
        return *current_scene;
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
