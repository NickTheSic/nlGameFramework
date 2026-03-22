#include "nl_lib.h"

#include "private/gl/nl_gl.h"

//https://www.youtube.com/watch?v=RqrkVmj-ntM

unsigned int endless_grid_shader_program;

// a reason to have a global camera and a scale, rotation and position separate?
mat4x4f endless_grid_view;
v3f camera_position = {0.f,0.f,0.f};
unsigned int ViewMat;
unsigned int CameraPosition;
unsigned int ScreenSize_loc;

internal_function void winsizecbk(int width, int height)
{
    float _w = (float)width/2.f;
    float _h = (float)height/2.f;

    create_orthographic_projection(&endless_grid_view, camera_position.x - _w, camera_position.x + _w, camera_position.y - _h, camera_position.y + _h, -10.0f, 10.0f);
    set_uniform_mat4x4f(endless_grid_shader_program, ViewMat, &endless_grid_view.m11);
    set_uniform_2f(endless_grid_shader_program, ScreenSize_loc, width, height);
}

void app_specific_init(void)
{
    set_window_size_callback(winsizecbk);

    endless_grid_shader_program = load_shader_from_files("endless_grid_2d.vs", "endless_grid_2d.fs");
    use_shader_program(endless_grid_shader_program);
    
    ViewMat = get_uniform_loc(endless_grid_shader_program, "ViewMat");

    CameraPosition = get_uniform_loc(endless_grid_shader_program, "CameraPosition");
    set_uniform_v3f(endless_grid_shader_program, CameraPosition, &camera_position.x);

    ScreenSize_loc = get_uniform_loc(endless_grid_shader_program, "ScreenSize");

    v2i screen = get_screen_size();
    winsizecbk(screen.x, screen.y);
}

void app_specific_update(double dt)
{
    unsigned char bTransformDirty = 0;
    const float speed = 50.f * dt;

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
        unsigned int CameraPosition = get_uniform_loc(endless_grid_shader_program, "CameraPosition");
        set_uniform_v3f(endless_grid_shader_program, CameraPosition, &camera_position.x);
        
        v2i screen = get_screen_size();
        winsizecbk(screen.x, screen.y);        
    }
}

void app_specific_render(void)
{
    use_shader_program(endless_grid_shader_program);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void app_specific_cleanup(void)
{
}