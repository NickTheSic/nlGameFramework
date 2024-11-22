#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "nl_sprite_renderer.h"

#define PLAYER_MAX_SPEED (150.0f)
#define PLAYER_WIDTH (50.0f)
#define PLAYER_HALF_WIDTH (PLAYER_WIDTH * 0.5f)
#define PLAYER_QUARTER_WIDTH (PLAYER_HALF_WIDTH * 0.5f)
#define PLAYER_DOUBLE_WIDTH (PLAYER_WIDTH * 2.0f)
#define GRAVITY_RAISE (PLAYER_DOUBLE_WIDTH + PLAYER_WIDTH)
#define GRAVITY_FALL  (GRAVITY_RAISE + PLAYER_DOUBLE_WIDTH + PLAYER_HALF_WIDTH)

typedef struct game_object game_object;
struct game_object
{
    nl_sprite sprite;
    v2f pos;
    float width;
    float height;
    float vertical_speed;

    char is_grounded;
};

typedef struct player_controller player_controller; 
struct player_controller
{
    nl_key left;
    nl_key right;
    nl_key jump;
};

void init_gameobject(game_object* const object, float width, float height, v2f start, const char* sprite_path);

void player_init(game_object* const player);
void player_update(double dt, game_object* const player, player_controller* const controller);

#endif//__PLAYER_H__