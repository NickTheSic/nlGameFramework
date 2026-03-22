#include "nl_lib.h"
#include "private/gl/nl_gl.h"

#include "endless_grid_2d.h"

//https://www.youtube.com/watch?v=RqrkVmj-ntM


// a reason to have a global camera and a scale, rotation and position separate?
mat4x4f endless_grid_view;
v3f camera_position = {0.f,0.f,0.f};

endless_grid_data egd = {0};

internal_function void winsizecbk(int width, int height)
{
    float _w = (float)width/2.f;
    float _h = (float)height/2.f;

    create_orthographic_projection(&endless_grid_view, camera_position.x - _w, camera_position.x + _w, camera_position.y - _h, camera_position.y + _h, -10.0f, 10.0f);
    //set_uniform_mat4x4f(egd.shader_program, egd.view_mat_loc, &endless_grid_view.m11);
    set_endless_grid_view_matrix(&egd, &endless_grid_view);
    set_endless_grid_screen_sizef(&egd, width, height);
}

void app_specific_init(void)
{
    set_window_size_callback(winsizecbk);

    init_endless_grid(&egd);
    set_endless_grid_camera_position(&egd, camera_position);

    v2i screen = get_screen_size();
    winsizecbk(screen.x, screen.y);
}

void app_specific_update(double dt)
{
    unsigned char bTransformDirty = 0;
    const float speed = 180.f * dt;

    if (key_is_held(key_w))
    {
        camera_position.y += speed;
        bTransformDirty = 1;
    }
    else if (key_is_held(key_s))
    {
        camera_position.y -= speed;
        bTransformDirty = 1;
    }

    if (key_is_held(key_d))
    {
        camera_position.x += speed;
        bTransformDirty = 1;
    }
    else if (key_is_held(key_a))
    {
        camera_position.x -= speed;
        bTransformDirty = 1;
    }

    if (key_is_held(key_up))
    {
        camera_position.z += speed;
    }
    else if (key_is_held(key_down))
    {
        camera_position.z -= speed;
    }

    if (bTransformDirty)
    {
        set_endless_grid_camera_position(&egd, camera_position);
        
        v2i screen = get_screen_size();
        winsizecbk(screen.x, screen.y);        
    }
}

void app_specific_render(void)
{
    render_endless_grid(&egd);
}

void app_specific_cleanup(void)
{
}

#include "endless_grid_2d.c"
