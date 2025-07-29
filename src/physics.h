#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include "window.h"

typedef struct Vector2D {
    float x;
    float y;
} Vector2D;

typedef struct RigidBody {
    Vector2D position;
    Vector2D velocity;
    Vector2D size;
    float mass;
    bool is_static;
} RigidBody;

typedef struct PhysicsWorld {
    RigidBody** bodies;
    int body_count;
    float gravity;
    float time_step;
} PhysicsWorld;

PhysicsWorld* create_world(float gravity, float time_step);
void destroy_world(PhysicsWorld* world);

RigidBody* create_body(float x, float y, float width, float height, float mass, bool is_static);
void add_body(PhysicsWorld* world, RigidBody* body);

void update_physics(PhysicsWorld* world);
bool check_collision(RigidBody* body1, RigidBody* body2);
void resolve_collision(RigidBody* body1, RigidBody* body2);

void draw_bodies(Window* window, PhysicsWorld* world);

#endif