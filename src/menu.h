#ifndef MENU_H
#define MENU_H

#include <SDL3/SDL.h>
#include <stdio.h>
#include "window.h"
#include "game.h"
#include "scene.h"



void menu();
void menu_handle_event(SDL_Event *event);
void menu_update(float delta_time);
void menu_render(NE_Window *window);

extern NE_Scene Menu_Scene;

NE_Scene *get_menu_scene();


#endif // MENU_H

