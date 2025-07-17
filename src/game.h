#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <SDL3/SDL.h>
#include "window.h"
#include "menu.h"
#include "scene.h"
#include "render.h"
#include "assets/assets.h"

void game();
void game_handle_event(SDL_Event *event);
void game_update();
void game_render(Window *window);
Scene *get_game_scene(); 

extern Scene Game_Scene;


#endif // GAME_H