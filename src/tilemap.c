#include "tilemap.h"

TileMap* load_tmx_file(const char* filepath) {
    char* xml = read_file(filepath);
    if (!xml) return NULL;

    char* map_tag = find_tag(xml, "map");
    if (!map_tag) { free(xml); return NULL; }

    TileMap* map = malloc(sizeof(TileMap));
    map->width = extract_attr_int(map_tag, "width");
    map->height = extract_attr_int(map_tag, "height");
    map->tile_width = extract_attr_int(map_tag, "tilewidth");
    map->tile_height = extract_attr_int(map_tag, "tileheight");

    int tile_count = map->width * map->height;
    map->tiles = malloc(sizeof(int) * tile_count);
    map->tile_count = tile_count;

    char* data_tag = find_tag(xml, "data");
    if (!data_tag) {
        free(xml);
        free(map->tiles);
        free(map);
        return NULL;
    }

    char* csv = extract_csv_data(data_tag);
    parse_csv(csv, map->tiles, tile_count);

    free(csv);
    free(xml);
    return map;
}

Texture* load_tileset(const char* path, Window *window) {


}


void render_tilemap(TileMap* map, Window *window){


}

void free_tilemap(TileMap* map) {
    if (map) {
        free(map->tiles);
        free(map);
    }
}
