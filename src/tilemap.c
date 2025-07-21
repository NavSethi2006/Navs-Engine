#include "tilemap.h"

TileMap* load_tmx(const char* filepath) {
    char* xml = read_file(filepath);
    if (!xml) return NULL;

    char* map_tag = find_tag(xml, "map");
    if (!map_tag) { free(xml); return NULL; }

    TileMap* map = malloc(sizeof(TileMap));
    map->width = extract_attr_int(map_tag, "width");
    map->height = extract_attr_int(map_tag, "height");
    map->tile_width = extract_attr_int(map_tag, "tilewidth");
    map->tile_height = extract_attr_int(map_tag, "tileheight");
    map->layer_count = 0;
   
    const char* search_ptr = xml;
    while((search_ptr = find_tag(search_ptr, "layer"))) {
        TileLayer* layer = &map->layers[map->layer_count++];
        layer->id = extract_attr_int(search_ptr, "id");
        extract_attr_string(search_ptr, "name", layer->name, sizeof(layer->name));
        layer->width = extract_attr_int(search_ptr, "width");
        layer->height = extract_attr_int(search_ptr, "height");
//        layer->opacity = extract_attr_float(search_ptr, "opacity");
//        layer->visible = extract_attr_int(search_ptr, "visible");

        int tile_count = layer->width * layer->height;
        layer->tiles = malloc(sizeof(int) * tile_count);
        memset(layer->tiles, 0, sizeof(int) * tile_count);

        char* data_tag = strstr(search_ptr, "<data");
        if(data_tag) {
            char* csv = extract_csv_data(data_tag);
            if(csv) {
                parse_csv(csv, layer->tiles, tile_count);
                free(csv);
            }
        }
        search_ptr = strstr(search_ptr + 1, "<layer");
    }  

    char* obj_group = strstr(xml, "<objectgroup");
    while (obj_group && map->object_layer_count < 8) {
        ObjectLayer *ol = &map->object_layers[map->object_layer_count++];
        extract_attr_string(obj_group, "name", ol->name, 64);
        ol->id = extract_attr_int(obj_group, "id");
        ol->object_count = 0;

        char* obj = strstr(obj_group, "<object");
        while (obj && ol->object_count < 256) {
            MapObject *o = &ol->objects[ol->object_count++];
            if (strstr(obj, "<object ")) {
            o->x = extract_attr_float(obj, "x");
            o->y = extract_attr_float(obj, "y");
            o->width = extract_attr_float(obj, "width");
            o->height = extract_attr_float(obj, "height");
            }
            else if(strstr(obj, "<objectgroup ")) {
                o->id = extract_attr_int(obj, "id");
            }

            obj = strstr(obj + 1, "<object");
        }

        obj_group = strstr(obj_group + 1, "<objectgroup");


    free(xml);
    return map;
    }
}

void load_tileset_into_map(TileMap *map, const char* xml) {
    Tileset tileset = {0};

    // Find <tileset> tag
    char* tileset_tag = strstr(xml, "<tileset");
    if (!tileset_tag) {
        fprintf(stderr, "No <tileset> found in TMX\n");
        exit(1);
    }

    tileset.firstgid     = extract_attr_int(tileset_tag, "firstgid");
    tileset.tile_width   = extract_attr_int(tileset_tag, "tilewidth");
    tileset.tile_height  = extract_attr_int(tileset_tag, "tileheight");
    tileset.tilecount    = extract_attr_int(tileset_tag, "tilecount");
    tileset.columns      = extract_attr_int(tileset_tag, "columns");

    // Find <image> tag within tileset
    char* image_tag = strstr(tileset_tag, "<image");
    if (!image_tag) {
        fprintf(stderr, "No <image> in <tileset>\n");
        exit(1);
    }

    const char* image_path =  extract_attr(image_tag, "source");
    Texture tileset_texture = get_texture_asset(image_path);

    tileset.image_width  = tileset_texture.width;
    tileset.image_height = tileset_texture.height;
    tileset.texture = &tileset_texture;

    map->tileset = tileset;
}


void render_tilemap(Window *window, TileMap *map){

    Tileset *tileset = &map->tileset;
    if(!tileset->texture) return;

    for(int i = 0; i < map->layer_count; i++) {
        TileLayer *layer = &map->layers[i];
        if(!layer->visible || !layer->tiles) continue;

        SDL_SetTextureAlphaMod(tileset->texture->Image, (Uint8)(layer->opacity * 255));

        for (int y = 0; y < layer->height; ++y) {
            for (int x = 0; x < layer->width; ++x) {
                uint32_t raw_gid = layer->tiles[y * layer->width + x];
                if ((raw_gid & GID_MASK) == 0) continue;

                int flip_h = raw_gid & FLIPPED_HORIZONTALLY;
                int flip_v = raw_gid & FLIPPED_VERTICALLY;
                int flip_d = raw_gid & FLIPPED_DIAGONALLY;

                uint32_t gid = raw_gid & GID_MASK;
                int tile_index = gid - tileset->firstgid;

                int src_x = (tile_index % tileset->columns) * tileset->tile_width;
                int src_y = (tile_index / tileset->columns) * tileset->tile_height;

                SDL_FRect dst = { x * tileset->tile_width, y * tileset->tile_height, tileset->tile_width, tileset->tile_height };
                SDL_FRect src = { src_x, src_y, tileset->tile_width, tileset->tile_height };

                SDL_FlipMode flip = SDL_FLIP_NONE;
                if (flip_h) flip |= SDL_FLIP_HORIZONTAL;
                if (flip_v) flip |= SDL_FLIP_VERTICAL;



                SDL_RenderTextureRotated(window->renderer, tileset->texture->Image, &src, &dst, 0.0, NULL, flip);
            }
        }

    }


}

void free_tilemap(TileMap* map) {
    if(!map) return;

    for (int i = 0; i < map->layer_count; i++) {
        free(map->layers[i].tiles);
    }
}
