#include "render.h"



void render_texture(Texture *texture, Window *window) {

    SDL_FRect dstrect = { texture->x, texture->y, texture->width, texture->height };

    SDL_RenderTexture(window->renderer, texture->Image, NULL, NULL);

}



