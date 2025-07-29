#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include "window.h"
#include "menu.h"
#include "scene.h"
#include "render.h"
#include "tilemap.h"
#include "assets/assets.h"
#include "viewport.h"
#include "physics.h"

void game();
void game_handle_event(SDL_Event *event);
void game_update(float delta_time);
void game_render(Window *window);
void game_free();
Scene *get_game_scene(); 

extern Scene Game_Scene;


#endif // GAME_H