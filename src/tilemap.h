/**
 * @file tilemap.h
 * @brief Handles loading and rendering of TMX tile maps and layers.
 */

 #ifndef TILEMAP_H
 #define TILEMAP_H
 
 #include "tmx/tmx.h"
 #include "render.h"
 #include "viewport.h"
 #include "window.h"
 #include "physics.h"


 /**
  * @struct TileMap
  * @brief Represents a loaded TMX tile map with rendering settings.
  */
 typedef struct NE_TileMap {
     tmx_map *map;             /**< Pointer to parsed TMX map. */
     NE_Texture tileset;          /**< The texture used for the tileset. */
     tmx_layer *layer;         /**< Pointer to the current layer. */
     tmx_tile **tiles;         /**< Array of all tile definitions. */
     NE_Viewport *vp;             /**< Camera/viewport used for rendering. */
     bool Debug_lines;         /**< Whether to draw debug outlines for objects. */
     int x, y;                 /**< Base position of the map in world space. */
 } NE_TileMap;


 /**
 * @brief Load a TMX tile map and prepare it for rendering.
 * @param path Path to the .tmx file.
 * @param x World x-position to place the map.
 * @param y World y-position to place the map.
 * @param draw_debug_for_obj_layer Whether to draw object outlines.
 * @return Pointer to the loaded TileMap.
 */
NE_TileMap* load_tmx_map(const char *path, int x, int y, bool draw_debug_for_obj_layer);

/**
 * @brief Get all object object layers in a x,y,width,height rectangle format
 * @param map Pointer to the TileMap to search
 * @param layer_name name of the object layer to search for, MUST BE THE EXACT NAME INSIDE THE TMX FILE
 * @param count_out Pointer to an integer to store the number of hitboxes found.
 * @return Array of Hitbox structs representing the objects in the layer.
 */
NE_Hitbox* get_object_layer(NE_TileMap *map, const char *layer_name, int *count_out);

/**
 * @brief Convert a TMX color (ARGB) to SDL_Color.
 * @param color 32-bit ARGB color from TMX.
 * @return SDL_Color equivalent.
 */
SDL_Color tmx_to_sdl_color(unsigned int color);

/**
 * @brief Load a texture from a image path.
 * @param path Path to the image resource.
 * @return Pointer to the loaded texture (as void* for compatibility).
 */
void* map_texture_loader(const char *path);

/**
 * @brief Render a single tile at a specific world coordinate.
 * @param window Pointer to the rendering Window.
 * @param map Pointer to the TileMap.
 * @param tile Pointer to the tile to draw.
 * @param x World x-position to draw the tile.
 * @param y World y-position to draw the tile.
 */
void draw_tile(NE_Window *window, NE_TileMap *map, tmx_tile *tile, int x, int y);

/**
 * @brief Render the current tile layer of the map.
 * @param window Pointer to the rendering Window.
 * @param map Pointer to the TileMap to render.
 */
void render_tile_layer(NE_Window *window, NE_TileMap *map);

/**
 * @brief Render a TMX object group layer.
 * @param window Pointer to the Window.
 * @param map Pointer to the TileMap.
 * @param objgrp Pointer to the TMX object group to render.
 */
void render_object_layer(NE_Window *window, NE_TileMap *map, tmx_object_group *objgrp);

/**
 * @brief Recursively render all layers in a TMX map.
 * @param window Pointer to the Window.
 * @param map Pointer to the TileMap.
 * @param layer Pointer to the TMX layer to render.
 */
void render_layers(NE_Window *window, NE_TileMap *map, tmx_layer *layer);

/**
 * @brief Render all tile and object layers in the map.
 * @param window Pointer to the Window.
 * @param map Pointer to the TileMap to render.
 */
void render_tmx_map(NE_Window *window, NE_TileMap *map);

/**
 * @brief Free all memory and textures associated with a tile map.
 * @param map Pointer to the TileMap to free.
 */
void free_tmx_map(NE_TileMap *map);
 
 #endif