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
    v2f estimated_movement = player->pos;

    if (player->is_grounded == 1)
    {
        if (key_was_pressed(controller->jump))
        {
            player->vertical_speed = GRAVITY_RAISE;
            play_sound(jump_sound);
        }
        player->is_grounded = 0;
    }

    if (player->is_grounded == 0)
    {
        if (player->vertical_speed <= 0.0f || !key_is_held(controller->jump))
        {
            player->vertical_speed -= (GRAVITY_FALL + 150) * dt;

            if (player->pos.y < 0.0f)
            {
                player->pos.y = 0.0f;
                player->vertical_speed = 0;
                player->is_grounded = 1;
            }
        }
        else
        {
            player->vertical_speed -= GRAVITY_RAISE * dt * 1.5f;
        }
    }

    estimated_movement.y += player->vertical_speed * dt;

    float horizontal_speed = {0};
    if (key_is_held(controller->right))
    {
        horizontal_speed += GRAVITY_FALL;
    }
    if (key_is_held(controller->left))
    {
        horizontal_speed -= GRAVITY_FALL;
    }

    estimated_movement.x += horizontal_speed * dt;

    // Check for collision with ground
    {
        aabb ground_box  = {0};
        ground_box.min.x = ground.pos.x;
        ground_box.min.y = ground.pos.y;
        ground_box.max.x = ground.pos.x + ground.width;
        ground_box.max.y = ground.pos.y + ground.height;

        if (estimated_movement.x != player->pos.x)
        {
            aabb player_box = {0};
            player_box.min.x = estimated_movement.x;
            player_box.min.y = player->pos.y;
            player_box.max.x = estimated_movement.x + player->width;
            player_box.max.y = player->pos.y + player->height;
            if (aabb_box_overlap(player_box, ground_box))
            {
                estimated_movement.x = player->pos.x;
            }
        }

        if (estimated_movement.y < player->pos.y)
        {
            aabb player_box = {0};
            player_box.min.x = player->pos.x;
            player_box.min.y = estimated_movement.y;
            player_box.max.x = player->pos.x + player->width;
            player_box.max.y = estimated_movement.y + player->height;

            if (aabb_box_overlap(player_box, ground_box))
            {
                estimated_movement.y = player->pos.y;
                player->vertical_speed = 0;
                player->is_grounded = 1;
            }
        }
    }

    player->pos.x = estimated_movement.x;
    player->pos.y = estimated_movement.y;
}
