#include "game.h"

Texture tex;
Texture tileset;
Animation_set *animations;
Animation *animation;
TileMap *tilemap;
Texture background;
Viewport *vp;


Frame RUN_ANIMATION[3] = {{0, 33, 20, 31},
                               {20, 33, 20, 31},
                               {40, 33, 20, 31}};

Frame IDLE_ANIMATION[1] = {0,0,17,32};

Frame JUMP_ANIMATION[5] = {{40, 80, 18, 31},
                               {70, 83, 16, 25},
                               {97, 86, 23, 20},
                               {129, 83, 18, 25},
                               {157, 84, 22, 23}};
                               
Frame WALL_CLIMB_ANIMATION[4] = {{0,199,17,32},
                                {40,201,17,32},
                                {80,200,16,31},
                            {118, 201, 23,31}};

Frame ATTACK_ANIMATION[4] = {{0,240,17,30},
                            {28,241,42,30},
                            {74,241,29,30},
                            {115,241,27,29}};

enum PlayerStates {
    IDLE,
    RUN,
    JUMP,
    WALL_CLIMB,
    ATTACK

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

    animations = init_animation_set(&tex, 5, 0, 0, 40, 51);

    animations->animations[IDLE] = init_animation(IDLE_ANIMATION, 1, 0.2f);
    animations->animations[RUN] = init_animation(RUN_ANIMATION, 3, 0.2f);
    animations->animations[JUMP] = init_animation(JUMP_ANIMATION, 5, 0.1f);
    animations->animations[ATTACK] = init_animation(ATTACK_ANIMATION, 4, 0.1f);
    animations->animations[WALL_CLIMB] = init_animation(WALL_CLIMB_ANIMATION, 4, 0.1f);
    PlayerStates = IDLE;

    tmx_img_load_func = (void*(*)(const char*))map_texture_loader;
    tmx_img_free_func = (void (*)(void*))SDL_DestroyTexture;

    tilemap = load_tmx_map("../src/assets/untitled.tmx",0, 0, false);   

    physicsworld = create_world(0, 1/120);
    player_body = create_body(50, 50, 50, 50, 1, false);
    ground = create_body(500, 500, 100, 100, 0, true);

    add_body(physicsworld, player_body);
    add_body(physicsworld, ground);

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

    player_body->velocity.x = 0;
    
    if(input.left) player_body->velocity.x = -move_speed;
    if(input.right) player_body->velocity.x = move_speed;
    if(input.up) player_body->velocity.y = -move_speed;
    if(input.down) player_body->velocity.y = move_speed;
    
    update_animation_set(animations, PlayerStates, delta_time);

    update_physics(physicsworld, delta_time);
}

void game_render(Window *window) {
    
    render_tmx_map(window, tilemap);
    draw_bodies(window, physicsworld);
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
