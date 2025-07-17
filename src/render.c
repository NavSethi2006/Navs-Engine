#include "render.h"


Texture load_texture(const char* file_path, int x, int y, int width, int height) {
    Texture texture;
    texture.Image = IMG_LoadTexture()
}


void render_texture(Texture *texture, Window *window) {
    if (!texture || !window || !texture->sdl_texture) {
        printf("Invalid texture or window for rendering.\n");
        return;
    }

    SDL_Rect dst_rect = {
        .x = (int)texture->x,
        .y = (int)texture->y,
        .w = (int)texture->width,
        .h = (int)texture->height
    };

    // Render the texture to the window's renderer
    if (SDL_RenderCopy(window->renderer, texture->sdl_texture, NULL, &dst_rect) < 0) {
        printf("Failed to render texture: %s\n", SDL_GetError());
    }
}
