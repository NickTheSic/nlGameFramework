#include "nl_lib.h"

#include "private/gl/nl_gl.h"

//https://www.youtube.com/watch?v=RqrkVmj-ntM

unsigned int endless_grid_shader_program;

// a reason to have a global camera and a scale, rotation and position separate?
mat4x4f endless_grid_view;
v3f camera_position = {0.f,0.f,0.f};
unsigned int ViewMat;
unsigned int CameraPosition;

unsigned int zero_quad;

internal_function void winsizecbk(int width, int height)
{
    float aspect = (float)width / (float)height;

    float _w = width/2.f;
    float _h = height/2.f;

    use_shader_program(endless_grid_shader_program);
    create_orthographic_projection(&endless_grid_view, -_w, _w, -_h, _h, -10.0f, 1000.0f);
    set_uniform_mat4x4f(ViewMat, &endless_grid_view.m11);
}

void app_specific_init(void)
{
    set_window_size_callback(winsizecbk);

    zero_quad = load_shader_from_files("zero_quad.vs", "zero_quad.fs");

    endless_grid_shader_program = load_shader_from_files("endless_grid_2d.vs", "endless_grid_2d.fs");
    use_shader_program(endless_grid_shader_program);
    
    v2i screen = get_screen_size();
    const float aspect = (float)screen.x/(float)screen.y;
    create_orthographic_projection(&endless_grid_view, -aspect, aspect, -1.0f, 1.0f, 0.0f, 10.0f);
    
    ViewMat = get_uniform_loc(endless_grid_shader_program, "ViewMat");
    set_uniform_mat4x4f(ViewMat, &endless_grid_view.m11);

    CameraPosition = get_uniform_loc(endless_grid_shader_program, "CameraPosition");
    set_uniform_v3f(CameraPosition, &camera_position.x);
}

void app_specific_update(double dt)
{
    unsigned char bTransformDirty = 0;

    if (key_is_held(key_w))
    {
        camera_position.y -= dt;
        bTransformDirty = 1;
    }
    else if (key_is_held(key_s))
    {
        camera_position.y += dt;
        bTransformDirty = 1;
    }

    if (key_is_held(key_d))
    {
        camera_position.x -= dt;
        bTransformDirty = 1;
    }
    else if (key_is_held(key_a))
    {
        camera_position.x += dt;
        bTransformDirty = 1;
    }

    if (key_is_held(key_up))
    {
        camera_position.z += dt;
    }
    else if (key_is_held(key_down))
    {
        camera_position.z -= dt;
    }

    if (bTransformDirty)
    {
        use_shader_program(endless_grid_shader_program);
        unsigned int CameraPosition = get_uniform_loc(endless_grid_shader_program, "CameraPosition");
        set_uniform_v3f(CameraPosition, &camera_position.x);
    }
}

void app_specific_render(void)
{
    use_shader_program(endless_grid_shader_program);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    use_shader_program(zero_quad);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void app_specific_cleanup(void)
{
}