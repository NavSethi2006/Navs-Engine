#include "viewport.h"


NE_Viewport* viewport_init(float x, float y, int width, int height, float zoom) {
    NE_Viewport *vp = malloc(sizeof(NE_Viewport));
    vp->x = x;
    vp->y = y;
    vp->width = width;
    vp->height = height;
    vp->zoom = zoom;
    return vp;
}

void viewport_move(NE_Viewport *vp, float destination_x, float destination_y) {
    vp->x += destination_x;
    vp->y += destination_y;
}

SDL_FRect viewport_get_view(NE_Viewport *vp) {
    return (SDL_FRect) {vp->x, vp->y, vp->width / vp->zoom, vp->height / vp->zoom};
}

SDL_FRect viewport_world_to_screen(NE_Viewport *vp, SDL_FRect world_rect) {
    return (SDL_FRect){(world_rect.x - vp->x) * vp->zoom,
                        (world_rect.y - vp->y) * vp->zoom,
                        world_rect.w * vp->zoom,
                        world_rect.h * vp->zoom};
}

bool camera_cull_rect(NE_Viewport *vp, SDL_FRect world_rect) {
    SDL_FRect view = viewport_get_view(vp);
    
    return world_rect.x + world_rect.w < view.x ||
           world_rect.y + world_rect.h < view.y ||
           world_rect.x > view.x + view.w ||
           world_rect.y > view.y + view.h;
}

void free_viewport(NE_Viewport *vp) {
    if (vp) {
        vp->x = 0;
        vp->y = 0;
        vp->width = 0;
        vp->height = 0;
        vp->zoom = 0;
        free(vp);
    }
}

