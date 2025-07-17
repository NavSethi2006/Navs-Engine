#include "render.h"


Texture load_texture(const char* file_path, int width, int height, Window* window) {
    Texture texture;

    int channels;

    unsigned char* img_data = stbi_load(file_path, width, height, channels, 4);

    if(!img_data) {
        SDL_Log("Failed to load image: %s", stbi_failure_reason());
    }

    SDL_Surface* surface = SDL_CreateSurfaceFrom(img_data, width, height, SDL_PIXELFORMAT_RGBA32, width * 4);

    if(!surface) {
        SDL_Log("Failed to create surface: %s", SDL_GetError());
        stbi_image_free(img_data);
    }

    texture.Image = SDL_CreateTextureFromSurface(window->renderer, surface);
    SDL_DestroySurface(surface);
    stbi_image_free(img_data);  
    
    return texture;

}


void render_texture(Texture *texture, Window *window) {

    SDL_RenderTexture(window->renderer, texture->Image, NULL, NULL);
    
}


