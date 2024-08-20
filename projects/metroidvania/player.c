#include "player.h"
#include "metroidvania.h"

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
            player->vertical_speed -= GRAVITY_RAISE * dt;
        }
    }

    if (player->is_grounded == 1)
    {
        if (key_was_pressed(controller->jump))
        {
            player->vertical_speed = GRAVITY_RAISE;
            player->is_grounded = 0;
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

    if (key_is_held(key_right))
    {
        camera_pos -= GRAVITY_FALL * dt;
        create_srt_matrix(&main_cam.view_matrix, (v3f){1.0f,1.0f,1.0f}, (v3f){0.0f,0.0f,0.0f}, (v3f){camera_pos,camera_pos,0.0f});
        u_view_mat = glGetUniformLocation(shader_program, "uViewMat");
        glUniformMatrix4fv(u_view_mat, 1, GL_FALSE, &main_cam.view_matrix.m11);
    }

    player->pos.x += horizontal_speed * dt;
}
