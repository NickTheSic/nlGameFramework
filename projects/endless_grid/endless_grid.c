#include "nl_lib.h"
#include "private/gl/nl_gl.h"

#include "endless_grid.h"

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
    set_uniform_mat4x4f(egd.shader_program, egd.view_mat_loc, &endless_grid_view.m11);
    set_uniform_2f(egd.shader_program, egd.screen_size_loc, width, height);
}

void app_specific_init(void)
{
    set_window_size_callback(winsizecbk);

    egd.shader_program = load_shader_from_files("endless_grid_2d.vs", "endless_grid_2d.fs");
    egd.view_mat_loc = get_uniform_loc(egd.shader_program, "ViewMat");
    egd.screen_size_loc = get_uniform_loc(egd.shader_program, "ScreenSize");
    egd.camera_pos_loc = get_uniform_loc(egd.shader_program, "CameraPosition");

    set_uniform_v3f(egd.shader_program, egd.camera_pos_loc, &camera_position.x);

    v2i screen = get_screen_size();
    winsizecbk(screen.x, screen.y);
}

void app_specific_update(double dt)
{
    unsigned char bTransformDirty = 0;
    const float speed = 80.f * dt;

    if (key_is_held(key_w))
    {
        camera_position.y -= speed;
        bTransformDirty = 1;
    }
    else if (key_is_held(key_s))
    {
        camera_position.y += speed;
        bTransformDirty = 1;
    }

    if (key_is_held(key_d))
    {
        camera_position.x -= speed;
        bTransformDirty = 1;
    }
    else if (key_is_held(key_a))
    {
        camera_position.x += speed;
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
        set_uniform_v3f(egd.shader_program, egd.camera_pos_loc, &camera_position.x);
        
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