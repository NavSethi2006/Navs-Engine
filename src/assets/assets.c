#include "assets.h"

static Asset* assets = NULL;
static SDL_Renderer* renderer = NULL;

void init_asset_manager(Window* window) {
    renderer = window->renderer;
}

Texture get_texture_asset(const char* file_path) {
    Texture texture = {0};  // Zero initialize

    // Search cache
    Asset* curr = assets;
    while (curr) {
        if (curr->key && strcmp(curr->key, file_path) == 0) {
            printf("Not In cache\n");
            return curr->texture;
        }
        curr = curr->next;
    }

    // Not found, load it
    if (!renderer) {
        printf("ERROR: renderer is NULL when loading '%s'\n", file_path);
        return texture;
    }

    texture.Image = IMG_LoadTexture(renderer, file_path);
    if (!texture.Image) {
        printf("Failed to load texture '%s': %s\n", file_path, SDL_GetError());
        return texture;
    }

    // Add to cache
    Asset* newAsset = malloc(sizeof(Asset));
    if (!newAsset) {
        printf("Memory allocation failed for Asset\n");
        return texture;
    }

    newAsset->key = strdup(file_path);
    newAsset->texture = texture;
    newAsset->next = assets;
    assets = newAsset;

    return texture;
}

void free_all_assets() {
    Asset* curr = assets;
    while (curr) {
        Asset* next = curr->next;
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