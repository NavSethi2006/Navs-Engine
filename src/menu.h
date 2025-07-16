#ifndef MENU_H
#define MENU_H

#include <SDL3/SDL.h>
#include <stdio.h>
#include "window.h"
#include "game.h"
#include "scene.h"



void menu();
void menu_handle_event(SDL_Event *event);
void menu_update();
void menu_render(Window *window);

extern Scene Menu_Scene;

Scene *get_menu_scene();


#endif // MENU_H

