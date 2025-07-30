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
    body->position.x = x;
    body->position.y = y;
    body->size.x = width;
    body->size.y = height;
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
        
        body->position.y += body->velocity.y * delta_time;
        body->position.x += body->velocity.x * delta_time;

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
    if (body1->position.x + body1->size.x < body2->position.x) return false;
    if (body1->position.x > body2->position.x + body2->size.x) return false;
    if (body1->position.y + body1->size.y < body2->position.y) return false;
    if (body1->position.y > body2->position.y + body2->size.y) return false;
    return true;
}

void resolve_collision(RigidBody* body1, RigidBody* body2) {

    if(body1->is_static && body2->is_static) return;

    float overlap_x = fmin(body1->position.x + body1->size.x, body2->position.x + body2->size.x) -
                        fmax(body1->position.x, body2->position.x);
    float overlap_y = fmin(body1->position.y + body1->size.y, body2->position.y + body2->size.y) -
                        fmax(body1->position.y, body2->position.y);

    if (overlap_x < overlap_y) {
        if (body1->position.x < body2->position.x) {
            body1->position.x -= overlap_x / 2;
            body2->position.x += overlap_x / 2;
        } else {
            body1->position.x += overlap_x / 2;
            body2->position.x -= overlap_x / 2;
        }
        if (!body1->is_static) body1->velocity.x = 0;
        if (!body2->is_static) body2->velocity.x = 0;

    } else {
        if (body1->position.y < body2->position.y) {
            body1->position.y -= overlap_y / 2;
            body2->position.y += overlap_y / 2;
        } else {
            body1->position.y += overlap_y / 2;
            body2->position.y -= overlap_y / 2;
        }
        if (!body1->is_static) body1->velocity.y = 0;
        if (!body2->is_static) body2->velocity.y = 0;
    }
}

void draw_bodies(Window* window, PhysicsWorld* world){
    SDL_SetRenderDrawColor(window->renderer, 255, 0, 0, 255);
    for (int i = 0; i < world->body_count; i++) {
        RigidBody* body = world->bodies[i];
        SDL_FRect rect = {body->position.x, body->position.y, body->size.x, body->size.y};
        SDL_RenderFillRect(window->renderer, &rect);
    }
}