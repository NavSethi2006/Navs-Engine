#include "assets.h"

static Asset* assets = NULL;
static SDL_Renderer* renderer = NULL;

void init_asset_manager(Window* window) {
    renderer = window->renderer;
}

Texture get_texture_asset(const char* file_path) {
// Look up in list

    Texture texture;
    Asset* curr = assets;
    while (curr) {
        if (strcmp(curr->key, file_path) == 0) return curr->texture;
        curr = curr->next;
    }

    // Not found, load it
    texture.Image = IMG_LoadTexture(renderer, file_path);
    if (!texture.Image) return texture;

    // Cache it
    Asset* newAsset = malloc(sizeof(Asset));
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