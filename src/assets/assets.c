#include "assets.h"

static Asset_Texture* texture_assets = NULL;
static Asset_Map* map_asset = NULL;
static SDL_Renderer* renderer = NULL;

void init_asset_manager(NE_Window* window) {
    renderer = window->renderer;
}

NE_Texture get_texture_asset(const char* file_path) {
    NE_Texture texture = {0};  // Zero initialize

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

void* map_texture_loader(const char *path) {
	NE_Texture tex = get_texture_asset(path);
	return (void*)tex.Image;
}

NE_TileMap* get_map_asset(const char* file_path, int x , int y, bool draw_debug_for_obj_layer) {
    NE_TileMap *map;

    Asset_Map* curr = map_asset;
    while (curr) {
        if (curr->key && strcmp(curr->key, file_path) == 0) {
            return curr->map;
        }
        curr = curr->next;        
    }

    map = load_tmx_map(file_path, x, y, draw_debug_for_obj_layer);

    Asset_Map *newAsset = malloc(sizeof(Asset_Map));
    newAsset->key = strdup(file_path);
    newAsset->map = map;
    newAsset->next = map_asset;
    map_asset = newAsset;
    
    printf("Loading map asset: %s\n", file_path);

    return map;

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
    texture_assets = NULL;
}
