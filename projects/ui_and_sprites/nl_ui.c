#include "nl_ui.h"
#include <private/nl_shader.h>
#include <private/gl/nl_gl.h>
#include "nl_mesh.h"

global_variable const char* nl_ui_vert_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec2 aPos;             \n"
"layout (location = 1) in vec2 aSize;             \n"
"uniform mat4 uViewMat;                                \n"
"const vec2 pos[] = vec2[4](vec2(-0.5,  0.5),vec2(-0.5, -0.5),vec2(0.5,   0.5),vec2(0.5,  -0.5));\n"
"void main() {                                         \n"
"vec2 offset = pos[gl_VertexID];\n"
" gl_Position = uViewMat * vec4(aPos.x + (offset.x * aSize.x) ,"
"                            aPos.y + (offset.y * aSize.y) ,"
                            "0.0,"
                            "1.0);"
"}                                                     \0";

global_variable const char* nl_ui_fragment_shader_code =
NL_SHADER_VERSION_HEADER
"out vec4 FragColor;                                   \n"
"void main() {                                         \n"
"    FragColor = oColor;                               \n"
"}                                                     \n";

global_variable nl_ui nl_ui_data = {0};

int ui_init()
{
    nl_ui_data.shader_data.shader_program = create_shader_program(nl_ui_vert_shader_code, nl_ui_fragment_shader_code);
    use_shader_program(nl_ui_data.shader_data.shader_program);
    nl_ui_data.shader_data.u_view_matrix = glGetUniformLocation(nl_ui_data.shader_data.shader_program, VIEW_MATRIX_UNIFORM_NAME);
    nl_ui_data.shader_data.u_world_matrix = glGetUniformLocation(nl_ui_data.shader_data.shader_program, WORLD_MATRIX_UNIFORM_NAME);

    initialize_camera_to_identity(&nl_ui_data.ui_camera);
    v2i screen_size = get_screen_size();
    ui_set_window_size(screen_size.x, screen_size.y);

    nl_ui_data.elements_max = 3;
    nl_ui_data.elements = (ui_element*)memory_allocate(sizeof(ui_element) * nl_ui_data.elements_max);

    return 1;
}

void ui_render()
{
    use_shader_program(nl_ui_data.shader_data.shader_program);
}

void ui_cleanup()
{
    memory_free(nl_ui_data.elements);
    free_shader_program(nl_ui_data.shader_data.shader_program);
}

void ui_set_window_size(int width, int height)
{
    create_orthographic_projection(&nl_ui_data.ui_camera.proj_matrix, 0.f, (float)width, 0.f, (float)height, -0.1f, 100.f);
    glUniformMatrix4fv(nl_ui_data.shader_data.u_view_matrix, 1, GL_FALSE, &nl_ui_data.ui_camera.proj_matrix.m11);
}
