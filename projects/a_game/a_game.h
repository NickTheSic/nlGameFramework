#pragma once

typedef struct object object;
struct object
{
    transform2d transform;
    mesh mesh;
};

typedef struct game_controls game_controls;
struct game_controls
{
    nl_key move_up;
    nl_key move_down;
    nl_key move_left;
    nl_key move_right;
};

typedef struct object_controller object_controller;
struct object_controller
{
    object* object;
    game_controls controls;
    float speed;
};
