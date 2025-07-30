#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <math.h>
#include "window.h"

/**
 * @struct Vector2D
 * @brief a vector for 2D spaces, consist of an x and a y coordinate
 */
typedef struct Vector2D {
    float x;
    float y;
} Vector2D;

/**
 * @struct RigidBody
 * @brief a rigidbody for 2d spaces, give physics and a hitbox for any object in the game
 */
typedef struct RigidBody {
    Vector2D position;
    Vector2D velocity;
    Vector2D size;
    float mass;
    bool is_static;
} RigidBody;

/**
 * @struct PhysicsWorld
 * @brief the physics world for all the physics need, activates collisions and everything to do with the rigidbody
 */
typedef struct PhysicsWorld {
    RigidBody** bodies;
    int body_count;
    float gravity;
    float time_step;
} PhysicsWorld;

/**
 * @brief create a physics world with specified parameters
 * @param gravity self explanitory, sets the gravity or 
 * @param time_step time it takes to update world
 * @return a pointer to the physics world struct
 */
PhysicsWorld* create_world(float gravity, float time_step);

/**
 * @brief destroy physics world
 * @param world pointer to physics world that you want to destroy
 */
void destroy_world(PhysicsWorld* world);

/**
 * @brief create a rigidbody with specified parameters
 * @param x x position of the rigidbody
 * @param y y position of the rigidbody
 * @param width width of the rigidbody (in pixels)
 * @param height height of the rigidbody (in pixels)
 * @param mass the mass of the rigidbody
 * @param is_static True if you dont want the body to be affected my the world
 * @return a pointer to a new rigidbody
 */
RigidBody* create_body(float x, float y, float width, float height, float mass, bool is_static);

/**
 * @brief add a rigidbody to the physics world specified
 * @param world the physics world
 * @param body the body you would like to add to said world
 */
void add_body(PhysicsWorld* world, RigidBody* body);

/**
 * @brief update the physics of the specified physics world
 * @param world the specified world that should be updated
 */
void update_physics(PhysicsWorld* world, float delta_time);
/**
 * @brief check if for collision between to rigidbodies
 * @param body1 the first body
 * @param body2 the second body
 * @return True if they have collided
 */
bool check_collision(RigidBody* body1, RigidBody* body2);

/**
 * @brief what happens after two bodies collided (stay still)
 * @param body1 the first body
 * @param body2 the second body
 */
void resolve_collision(RigidBody* body1, RigidBody* body2);

/**
 * @brief for debug purposes
 * @param window the active window
 * @param world the world you would like to debug
 */
void draw_bodies(Window* window, PhysicsWorld* world);

#endif