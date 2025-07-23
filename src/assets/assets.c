#include "assets.h"

static Asset_Texture* texture_assets = NULL;
static Asset_Map* map_asset = NULL;
static SDL_Renderer* renderer = NULL;

void init_asset_manager(Window* window) {
    renderer = window->renderer;
}



Texture get_texture_asset(const char* file_path) {
    Texture texture = {0};  // Zero initialize

    // Search cache
    Asset_Texture* curr = texture_assets;
    while (curr) {
        if (curr->key && strcmp(curr->key, file_path) == 0) {
            return curr->texture;
        }
        curr = curr->next;
    }

    // Not found, load it

    texture.Image = IMG_LoadTexture(renderer, file_path);
    if (!texture.Image) {
        printf("Failed to load texture '%s': %s\n", file_path, SDL_GetError());
    }

    // Add to cache
    Asset_Texture* newAsset = malloc(sizeof(Asset_Texture));
    if (!newAsset) {
        printf("Memory allocation failed for Asset\n");
    }

    newAsset->key = strdup(file_path);
    newAsset->texture = texture;
    newAsset->next = texture_assets;
    texture_assets = newAsset;

    return texture;
}

SDL_Renderer *get_renderer() {
    return renderer;
}

void free_all_assets() {
    Asset_Texture* curr = texture_assets;
    while (curr) {
        Asset_Texture* next = curr->next;
        SDL_DestroyTexture(curr->texture.Image);
        curr->texture.height = 0;
        curr->texture.width = 0;
        curr->texture.x = 0;
        curr->texture.y = 0;
        free(curr->key);
        free(curr);
        curr = next;
    }
    assets = NULL;
}
