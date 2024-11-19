#ifndef __PLAYER_H__
#define __PLAYER_H__

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
    mesh mesh;
    v2f pos;
    float vertical_speed;
    float width;

    char is_grounded;
};

typedef struct player_controller player_controller; 
struct player_controller
{
    nl_key left;
    nl_key right;
    nl_key jump;
};

void player_init(game_object* const player);
void player_update(double dt, game_object* const player, player_controller* const controller);

#endif//__PLAYER_H__