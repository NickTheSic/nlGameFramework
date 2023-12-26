#include "nl_lib.h"
#include "private/nl_gl.h"


#include "my_ui_types.h"


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

const char* fragment_shader_code =
NL_SHADER_VERSION_HEADER
"out vec4 FragColor;                                   \n"
"in vec4 oColor;                                       \n"
"void main() {                                         \n"
"    FragColor = oColor;                               \n"
"}                                                     \0";

unsigned int shader_program;


global_variable ui_camera camera = {0};
global_variable ui_element_data MAX_ELEMENTS[10];

global_variable v2i mouse_click_pos;
global_variable v2i last_mouse_pos;
global_variable int active_element;
global_variable int editing;

void app_specific_init(void)
{
    ui_camera_initialize_screen_size(&camera, get_screen_size());

    shader_program = create_shader_program(vert_shader_code, fragment_shader_code);
    glUseProgram(shader_program);
    unsigned int transformLoc = glGetUniformLocation(shader_program, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &camera.matrix.m11);
}

void app_specific_update(double dt)
{
    if (was_mouse_button_pressed(NL_MOUSE_BUTTON_LEFT))
    {
        editing = 1;
        mouse_click_pos = get_mouse_position_from_system();
        last_mouse_pos = mouse_click_pos;
        NL_LOG("Clicked %d %d", mouse_click_pos.x,  mouse_click_pos.y);
    }

    if (editing == 1)
    {
        v2i current_mouse_pos = get_mouse_position_from_system();
        if (current_mouse_pos.x != last_mouse_pos.x || current_mouse_pos.y != last_mouse_pos.y)
        {
            NL_LOG("Currently %d %d", current_mouse_pos.x,  current_mouse_pos.y);
            last_mouse_pos = current_mouse_pos;
        }

        if (was_mouse_button_released(NL_MOUSE_BUTTON_LEFT))
        {
            editing = 0;
            active_element++;
        }
    }
}

void ui_camera_initialize_screen_size(ui_camera *const camera, v2i screen_size)
{
    create_orthographic_projection(
        &camera->matrix, 
        0, 
        screen_size.x,
        0, 
        -screen_size.y,
        -0.1, 100
    );
}
