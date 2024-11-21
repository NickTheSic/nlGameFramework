#include "player.h"

global_variable unsigned int jump_sound = {0};

void player_init(game_object* const player)
{
    jump_sound = load_sound_file("data/retrogamesfx.wav");

    player->width = PLAYER_WIDTH;
    player->pos = (v2f){100.0f,100.0f};
    generate_square_simple_sprite(&player->mesh, player->width, (colourf){1.0f,0.5f,0.2f,1.0f});
    //generate_circle_mesh(&player->mesh, player->width, 16);
}

void player_update(double dt, game_object* const player, player_controller* const controller)
{
    if (player->is_grounded == 0)
    {
        if (player->vertical_speed <= 0.0f)
        {
            player->vertical_speed -= (GRAVITY_FALL + 150) * dt;
        }
        else
        {
            player->vertical_speed -= GRAVITY_RAISE * dt * 1.5f;
        }
    }

    if (player->is_grounded == 1)
    {
        if (key_was_pressed(controller->jump))
        {
            player->vertical_speed = GRAVITY_RAISE;
            player->is_grounded = 0;
            play_sound(jump_sound);
        }
    }

    if (player->pos.y < 0.0f)
    {
        player->pos.y = 0.0f;
        player->vertical_speed = 0;
        player->is_grounded = 1;
    }
    player->pos.y += player->vertical_speed * dt;

    float horizontal_speed = {0};
    if (key_is_held(controller->right))
    {
        horizontal_speed += GRAVITY_FALL;
    }
    if (key_is_held(controller->left))
    {
        horizontal_speed -= GRAVITY_FALL;
    }

    player->pos.x += horizontal_speed * dt;
}
