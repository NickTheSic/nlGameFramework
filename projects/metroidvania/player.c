#include "player.h"

global_variable unsigned int jump_sound = {0};

void init_gameobject(game_object* const object, float width, float height, v2f start, const char* sprite_path)
{
    object->width = width;
    object->height = height;
    object->pos = start;
    generate_rectangle_simple_sprite(&object->sprite, object->width, object->height);
    load_texture_for_sprite(&object->sprite, sprite_path);
}

void player_init(game_object* const player)
{
    jump_sound = load_sound_file("data/retrogamesfx.wav");

    init_gameobject(player, PLAYER_WIDTH, PLAYER_WIDTH, (v2f){100.f,100.f}, "data/thing.png");
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
