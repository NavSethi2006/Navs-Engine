#include "game.h"

Texture tex;
Texture tileset;
Animation_set *animations;
Animation *animation;
TileMap *tilemap;
Texture background;
Viewport *vp;


Frame WALK_DOWN_ANIMATION[4] = {{0,0,12,16},
                               {15,0,13,16},
                               {32,1,12,15},
                                {46,0,13,16}};
Frame WALK_UP_ANIMATION[4] = {{0,49,12,15},
                              {15,48,13,16},
                              {31,48,12,16},
                              {48,48,13,16}};
Frame WALK_RIGHT_ANIMATION[4] = {{0,33,10,15},
                                 {16,32,10,16},
                                 {32,33,10,15},
                                 {47,32,10,16}};
Frame WALK_LEFT_ANIMATION[4] = {{0,17,10,15},
                                {16,16,10,16},
                                {32,17,10,15},
                                {47,16,10,16}};
Frame IDLE_ANIMATION_DOWN[1] = {15,0,13,16};
Frame IDLE_ANIMATION_UP[1] = {15,48,13,16};
Frame IDLE_ANIMATION_RIGHT[1] = {16,32,10,16};
Frame IDLE_ANIMATION_LEFT[1] = {16,16,10,16};


enum PlayerStates {
    IDLE_DOWN,
    IDLE_UP,
    IDLE_RIGHT,
    IDLE_LEFT,
    WALK_DOWN,
    WALK_LEFT,
    WALK_RIGHT,
    WALK_UP

} PlayerStates;


PhysicsWorld *physicsworld;
RigidBody *player_body;
RigidBody *ground;

typedef struct {
    bool left, right, up, down, jump, attack;
} InputState;

InputState input = {0};


void game() {

    vp = viewport_init(0, 0, 1600, 800, 1);

    set_render_viewport(vp);

    tex = get_texture_asset("../src/assets/player.png");

    animations = init_animation_set(&tex, 8, 0, 0, 10*5, 16*5);

    animations->animations[IDLE_DOWN] = init_animation(IDLE_ANIMATION_DOWN, 1, 0.2f);
    animations->animations[IDLE_UP] = init_animation(IDLE_ANIMATION_UP, 1, 0.2f);
    animations->animations[IDLE_RIGHT] = init_animation(IDLE_ANIMATION_RIGHT, 1, 0.2f);
    animations->animations[IDLE_LEFT] = init_animation(IDLE_ANIMATION_LEFT, 1, 0.2f);

    animations->animations[WALK_DOWN] = init_animation(WALK_DOWN_ANIMATION, 4, 0.2f);
    animations->animations[WALK_UP] = init_animation(WALK_UP_ANIMATION, 4, 0.2f);
    animations->animations[WALK_RIGHT] = init_animation(WALK_RIGHT_ANIMATION, 4, 0.2f);
    animations->animations[WALK_LEFT] = init_animation(WALK_LEFT_ANIMATION, 4, 0.2f);
    PlayerStates = IDLE_RIGHT;

    tmx_img_load_func = (void*(*)(const char*))map_texture_loader;
    tmx_img_free_func = (void (*)(void*))SDL_DestroyTexture;

    tilemap = load_tmx_map("../src/assets/untitled.tmx",0, 0, false);   

    physicsworld = create_world(0, 1/120);
    player_body = create_body(tex.x, tex.y, tex.width, tex.height, 1, false);
    ground = create_body(500, 500, 100, 100, 0, true);

    int hitbox_count;

    Hitbox* hitbox = get_object_layer(tilemap, "Collision", &hitbox_count);

    for (int i = 0; i < hitbox_count; i++) {
        RigidBody* body = create_body(hitbox[i].position.x, hitbox[i].position.y, hitbox[i].size.x, hitbox[i].size.y, 0, true);
        add_body(physicsworld, body);
    }

    add_body(physicsworld, player_body);

}


void game_handle_event(SDL_Event *event) {

    if(event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE) {
        switch_scene(get_menu_scene());
    }
    if(event->type == SDL_EVENT_KEY_DOWN || event->type == SDL_EVENT_KEY_UP) {
        bool state = (event->type == SDL_EVENT_KEY_DOWN);
        
        switch(event->key.key) {
            case SDLK_A: input.left = state; break;
            case SDLK_D: input.right = state; break;
            case SDLK_W: input.up = state; break;
            case SDLK_S: input.down = state; break;
            case SDLK_SPACE: input.jump = state; break;
        }
    }
}

const float move_speed = 400.0f;


void game_update(float delta_time) {
    
    if(input.left)player_body->velocity.x = -move_speed;
    if(input.right)player_body->velocity.x = move_speed;
    if(input.up)player_body->velocity.y = -move_speed;
    if(input.down)player_body->velocity.y = move_speed;

    if(player_body->velocity.x < 0) {
        PlayerStates = WALK_LEFT;
    } else if(player_body->velocity.x > 0) {
        PlayerStates = WALK_RIGHT;
    } else if(player_body->velocity.y < 0) {
        PlayerStates = WALK_UP;
    } else if(player_body->velocity.y > 0) {
        PlayerStates = WALK_DOWN;
    } else {
        if(PlayerStates == WALK_LEFT) PlayerStates = IDLE_LEFT;
        else if(PlayerStates == WALK_RIGHT) PlayerStates = IDLE_RIGHT;
        else if(PlayerStates == WALK_UP) PlayerStates = IDLE_UP;
        else if(PlayerStates == WALK_DOWN) PlayerStates = IDLE_DOWN;
    }

    animations->texture->x = player_body->hitbox.position.x;
    animations->texture->y = player_body->hitbox.position.y;

    vp->x = player_body->hitbox.position.x - (vp->width / 2);
    vp->y = player_body->hitbox.position.y - (vp->height / 2);

    update_animation_set(animations, PlayerStates, delta_time);

    update_physics(physicsworld, delta_time);

}

void game_render(Window *window) {
    
    render_tmx_map(window, tilemap);
//    draw_bodies(window, physicsworld);
    render_animation_set(animations, PlayerStates, window);
}

void game_free() {
    free_viewport(vp);
    free_tmx_map(tilemap);

}


Scene Game_Scene = {
    .init  = game,
    .handle_event = game_handle_event,
    .update = game_update,
    .render = game_render,
    .free = game_free,
};

Scene *get_game_scene() {
    return &Game_Scene;
}
