#include "camera_control.h"

#include <private/nl_math.h>
#include <private/nl_shader.h>

global_variable float camera_pos_x = {0};
global_variable float camera_pos_y = {0};

extern unsigned int shader_program;

void camera_controls(float dt, camera* const cam)
{
    char bIsDirty = 0;

    if (key_is_held(key_right))
    {
        camera_pos_x -= GRAVITY_FALL * dt;
        bIsDirty = 1;
    }
    else if (key_is_held(key_left))
    {
        camera_pos_x += GRAVITY_FALL * dt;
        bIsDirty = 1;
    }

    if (key_is_held(key_up))
    {
        camera_pos_y -= GRAVITY_FALL * dt;
        bIsDirty = 1;
    }
    else if (key_is_held(key_down))
    {
        camera_pos_y += GRAVITY_FALL * dt;
        bIsDirty = 1;
    }

    if (bIsDirty > 0)
    {
        create_srt_matrix(&cam->view_matrix, (v3f){1.0f,1.0f,1.0f}, (v3f){0.0f,0.0f,0.0f}, (v3f){camera_pos_x,camera_pos_y,0.0f});
        u_view_mat = get_uniform_loc(shader_program, "uViewMat");
        set_uniform_mat4x4f(u_view_mat, &cam->view_matrix.m11);
    }
}
