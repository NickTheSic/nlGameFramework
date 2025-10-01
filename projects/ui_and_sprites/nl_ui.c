#include "nl_ui.h"
#include <private/nl_shader.h>
#include <private/gl/nl_gl.h>
#include "nl_mesh.h"

global_variable const char* nl_ui_vert_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec3 aPos;                   \n"
"layout (location = 1) in vec4 aColor;                 \n"
"uniform mat4 uWorldMat;                               \n"
"uniform mat4 uViewMat;                                \n"
"out vec4 oColor;                                      \n"
"void main() {                                         \n"
"   vec4 worldPos = uWorldMat * vec4(aPos, 1.0);       \n"
"   gl_Position = uViewMat * worldPos;                 \n"
"   oColor = aColor;                                   \n"
"}                                                     \0";

global_variable const char* nl_ui_fragment_shader_code =
NL_SHADER_VERSION_HEADER
"out vec4 FragColor;                                   \n"
"in vec4 oColor;                                       \n"
"void main() {                                         \n"
"    FragColor = oColor;                               \n"
"}                                                     \n";

global_variable nl_ui nl_ui_data = {0};

void initialize_object(ui_element* o, v2f anchor)
{
    generate_mesh_using_vertices_and_indices(&o->m, square_verts, 4, square_indices, 6);

    o->anchor.x = anchor.x;
    o->anchor.y = anchor.y;

    initialize_transform2d(&o->transform);
}

int ui_init()
{
    nl_ui_data.shader_data.shader_program = create_shader_program(nl_ui_vert_shader_code, nl_ui_fragment_shader_code);
    use_shader_program(nl_ui_data.shader_data.shader_program);
    NL_LOG("Shader Program: %d", nl_ui_data.shader_data.shader_program);
    nl_ui_data.shader_data.u_view_matrix = glGetUniformLocation(nl_ui_data.shader_data.shader_program, "uViewMat");
    NL_LOG("View Matrix Loc: %d", nl_ui_data.shader_data.u_view_matrix)
    nl_ui_data.shader_data.u_world_matrix = glGetUniformLocation(nl_ui_data.shader_data.shader_program, "uWorldMat");
    NL_LOG("World Matrix Loc: %d", nl_ui_data.shader_data.u_world_matrix)

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
    create_orthographic_projection(&nl_ui_data.ui_camera.view_matrix, 0.f, (float)width, 0.f, (float)height, -0.1f, 100.f);
    glUniformMatrix4fv(nl_ui_data.shader_data.u_view_matrix, 1, GL_FALSE, &nl_ui_data.ui_camera.view_matrix.m11);
}

void ui_set_world_matrix(const float* const matrix_11)
{
    glUniformMatrix4fv(nl_ui_data.shader_data.u_world_matrix, 1, GL_FALSE, matrix_11);
}

