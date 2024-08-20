#ifndef __PLAYER_H__
#define __PLAYER_H__

#define PLAYER_MAX_SPEED (150.0f)
#define PLAYER_WIDTH (50.0f)
#define PLAYER_HALF_WIDTH (PLAYER_WIDTH * 0.5f)
#define PLAYER_QUARTER_WIDTH (PLAYER_HALF_WIDTH * 0.5f)
#define PLAYER_DOUBLE_WIDTH (PLAYER_WIDTH * 2.0f)
#define GRAVITY_RAISE (PLAYER_DOUBLE_WIDTH + PLAYER_HALF_WIDTH)
#define GRAVITY_FALL  (GRAVITY_RAISE + PLAYER_DOUBLE_WIDTH + PLAYER_HALF_WIDTH)

void player_update(double dt, struct game_object* const player, struct player_controller* const controller);

#endif//__PLAYER_H__