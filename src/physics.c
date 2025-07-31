#include "physics.h"

PhysicsWorld* create_world(float gravity, float time_step) {
    PhysicsWorld* world = malloc(sizeof(PhysicsWorld));
    world->gravity = gravity;
    world->time_step = time_step;
    world->body_count = 0;
    world->bodies = NULL;
    return world;
}

void destroy_world(PhysicsWorld* world) {
    for (int i = 0; i < world->body_count; i++) {
        free(world->bodies[i]);
    }
    free(world->bodies);
    free(world);
}

RigidBody* create_body(float x, float y, float width, float height, float mass, bool is_static) {
    RigidBody* body = malloc(sizeof(RigidBody));
    body->hitbox.position.x = x;
    body->hitbox.position.y = y;
    body->hitbox.size.x = width;
    body->hitbox.size.y = height;
    body->is_static = is_static;
    body->velocity.x = 0;
    body->velocity.y = 0;
    body->mass = is_static ? 0 : mass;
    return body;
}

void add_body(PhysicsWorld* world, RigidBody* body) {
    world->bodies = realloc(world->bodies, sizeof(RigidBody*) * (world->body_count + 1));
    world->bodies[world->body_count++] = body;
}

void update_physics(PhysicsWorld* world, float delta_time) {
    for (int i = 0; i < world->body_count; i++) {
        RigidBody* body = world->bodies[i];
        if(body->is_static) continue;
        
        body->hitbox.position.x += body->velocity.x * delta_time;
        body->hitbox.position.y += body->velocity.y * delta_time;

        body->velocity.y = 0;
        body->velocity.x = 0;
    }    

    for (int i = 0; i < world->body_count; i++) {
        for (int j = i+1; j < world->body_count; j++) {
            if(check_collision(world->bodies[i], world->bodies[j])) {
                resolve_collision(world->bodies[i], world->bodies[j]);
            }
        }
    }
}

bool check_collision(RigidBody* body1, RigidBody* body2) {
    if (body1->hitbox.position.x + body1->hitbox.size.x < body2->hitbox.position.x) return false;
    if (body1->hitbox.position.x > body2->hitbox.position.x + body2->hitbox.size.x) return false;
    if (body1->hitbox.position.y + body1->hitbox.size.y < body2->hitbox.position.y) return false;
    if (body1->hitbox.position.y > body2->hitbox.position.y + body2->hitbox.size.y) return false;
    return true;
}


void resolve_collision(RigidBody* body1, RigidBody* body2) {

    if (body1->is_static && body2->is_static) return;

    float overlap_x = fmin(body1->hitbox.position.x + body1->hitbox.size.x, body2->hitbox.position.x + body2->hitbox.size.x) -
                     fmax(body1->hitbox.position.x, body2->hitbox.position.x);
    float overlap_y = fmin(body1->hitbox.position.y + body1->hitbox.size.y, body2->hitbox.position.y + body2->hitbox.size.y) -
                     fmax(body1->hitbox.position.y, body2->hitbox.position.y);

    if (overlap_x < overlap_y) {
        // Horizontal collision resolution
        if (body1->hitbox.position.x < body2->hitbox.position.x) {
            if (!body1->is_static) body1->hitbox.position.x -= overlap_x;
            if (!body2->is_static) body2->hitbox.position.x += overlap_x;
        } else {
            if (!body1->is_static) body1->hitbox.position.x += overlap_x;
            if (!body2->is_static) body2->hitbox.position.x -= overlap_x;
        }
        
        // Reset velocities
        if (!body1->is_static) body1->velocity.x = 0;
        if (!body2->is_static) body2->velocity.x = 0;
    } else {
        // Vertical collision resolution
        if (body1->hitbox.position.y < body2->hitbox.position.y) {
            if (!body1->is_static) body1->hitbox.position.y -= overlap_y;
            if (!body2->is_static) body2->hitbox.position.y += overlap_y;
        } else {
            if (!body1->is_static) body1->hitbox.position.y += overlap_y;
            if (!body2->is_static) body2->hitbox.position.y -= overlap_y;
        }
        
        // Reset velocities
        if (!body1->is_static) body1->velocity.y = 0;
        if (!body2->is_static) body2->velocity.y = 0;
    }
}

void draw_bodies(Window* window, PhysicsWorld* world){
    SDL_SetRenderDrawColor(window->renderer, 255, 0, 0, 255);
    for (int i = 0; i < world->body_count; i++) {
        RigidBody* body = world->bodies[i];
        SDL_FRect rect = {body->hitbox.position.x, body->hitbox.position.y, body->hitbox.size.x, body->hitbox.size.y};
        SDL_RenderRect(window->renderer, &rect);
    }
}