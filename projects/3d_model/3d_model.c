#include "nl_lib.h"
#include "private/nl_gl.h"
#include "string.h" //memcpy

const char* vert_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec3 aPos;                   \n"
"layout (location = 1) in vec4 aColor;                 \n"
"uniform mat4 transform;                               \n"
"out vec4 oColor;                                      \n"
"void main() {                                         \n"
"   gl_Position = transform * vec4(aPos, 1.0);         \n"
"   oColor = aColor;                                   \n"
"}                                                     \0";

mesh untitled = {0};
mat4x4f matrix = {0};

float camera_bounds = 1.f;

// Required - Could be renderer or material
unsigned int shader_program;

void _recalculate_camera()
{
    create_orthographic_projection(&matrix, -camera_bounds, camera_bounds, -camera_bounds, camera_bounds, -0.1, 100);
}

void app_specific_init(void)
{
    load_mesh_from_file("data/untitled.obj", &untitled);

    _recalculate_camera();

    shader_program = create_shader_program(vert_shader_code, common_fragment_shader_code);
    glUseProgram(shader_program);

    set_depth_test_enabled(1);
}

void app_specific_update(double dt)
{
    if (key_was_pressed(key_a) || key_was_released(key_a))
    {
        matrix.m11 = -matrix.m11;
    }
    if (key_was_pressed(key_s) || key_was_released(key_s))
    {
        matrix.m22 = -matrix.m22;
    }
    if (mouse_button_is_held(NL_MOUSE_BUTTON_LEFT))
    {
        matrix.m33 = -matrix.m33;
    }

    if (key_was_pressed(key_d))
    {
        set_depth_test_enabled(0);
    }
    else if (key_was_released(key_d))
    {
        set_depth_test_enabled(1);
    }

    camera_bounds += get_mouse_scroll_this_frame() * dt;
    if (get_mouse_scroll_this_frame() != 0)
    {
        _recalculate_camera();
    }
}
void app_specific_render(void)
{
    glUseProgram(shader_program);
    unsigned int transformLoc = glGetUniformLocation(shader_program, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &matrix.m11);
    
    render_single_mesh(&untitled);
    set_wireframe_rendering(); 
    glClear(GL_DEPTH_BUFFER_BIT);
    render_single_mesh(&untitled);
    set_fill_rendering();
}

void app_specific_cleanup(void)
{
    free_mesh(&untitled);
}
