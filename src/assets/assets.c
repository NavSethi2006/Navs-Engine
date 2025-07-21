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
            printf("Not In cache\n");
            return curr->texture;
        }
        curr = curr->next;
    }

    // Not found, load it

    texture.Image = IMG_LoadTexture(renderer, file_path);
    if (!texture.Image) {
        printf("Failed to load texture '%s': %s\n", file_path, SDL_GetError());
        return texture;
    }

    // Add to cache
    Asset_Texture* newAsset = malloc(sizeof(Asset_Texture));
    if (!newAsset) {
        printf("Memory allocation failed for Asset\n");
        return texture;
    }

    newAsset->key = strdup(file_path);
    newAsset->texture = texture;
    newAsset->next = texture_assets;
    texture_assets = newAsset;

    return texture;
}

/*
TileMap *get_tilemap_asset(const char* map_path) {
    TileMap *map;
    // search cache
     
    Asset_Map* curr = map_asset;
    while (curr) {
        if (curr->key && strcmp(curr->key, map_path) == 0) {
            printf("Not In cache\n");
            return map;
        }
        curr = curr->next;
    }

    map = load_tmx(map_path);
    if (!map) {
        printf("Could not load : %s\n", map_path);
        return map;
    }

    Asset_Map* newAsset = malloc(sizeof(Asset_Map));
    if (!newAsset) {
        printf("Memory allocation failed for Asset\n");
        return map;
    }

    newAsset->key = strdup(map_path);
    newAsset->map = map;
    newAsset->next = map_asset;
    map_asset = newAsset;

    return map;
}
*/

/*
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
*/