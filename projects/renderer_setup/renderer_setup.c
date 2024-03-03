#include "nl_lib.h"
#include "private/nl_gl.h"

const char* vert_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec3 aPos;                   \n"
"layout (location = 1) in vec4 aColor;                 \n"
"uniform mat4 uWorldMat;                               \n"
"uniform mat4 uViewMat;                                \n"
"out vec4 oColor;                                      \n"
"void main() {                                         \n"
"   vec4 worldPos = uWorldMat * vec4(aPos.x, aPos.y, aPos.z, 1.0);   \n"
"   gl_Position = uViewMat * worldPos;                 \n"
"   oColor = aColor;                                   \n"
"}                                                     \0";

const char* fragment_shader_code =
NL_SHADER_VERSION_HEADER
"out vec4 FragColor;                                   \n"
"in vec4 oColor;                                       \n"
"void main() {                                         \n"
"    FragColor = oColor;                               \n"
"}                                                     \0";

mesh triangle;
mesh square;

camera main_camera;

vertex_data vertices[] = 
{
    {{-0.5f, -0.5f, -1.0f}, {1.0f, 0.5f, 0.8f, 1.0f}},
    {{ 0.5f, -0.5f, 1.0f}, {1.0f, 0.5f, 0.8f, 1.0f}},
    {{ 0.0f,  0.5f, 0.0f}, {1.0f, 0.5f, 0.8f, 1.0f}}
};

vertex_data square_verts[] =
{
    {{-0.5f, -0.5f, 2.0f}, {1.0f, 0.5f, 0.8f, 1.0f}},
    {{ 0.5f, -0.5f, 0.0f}, {0.8f, 1.0f, 0.5f, 1.0f}},
    {{ 0.5f,  0.5f, -2.0f}, {0.5f, 0.8f, 1.0f, 1.0f}},
    {{-0.5f,  0.5f, 0.0f}, {0.7f, 0.2f, 0.0f, 1.0f}}
};

unsigned int square_indices[] =
{
    0,1,2,
    2,3,0
};

// Required - Could be renderer or material
unsigned int shader_program;

void app_specific_init(void)
{
    generate_mesh_using_vertices_and_indices(&triangle, vertices, 3, square_indices, 3);
    generate_mesh_using_vertices_and_indices(&square, square_verts, 4, square_indices, 6);
    
    shader_program = create_shader_program(vert_shader_code, fragment_shader_code);
    use_shader_program(shader_program);
}

void app_specific_update(double dt)
{
    (void)dt;
    
    use_shader_program(shader_program);

    mat4x4f view = {0};
    create_identity_matrix(&view);
    create_orthographic_projection(&view,-2.f,2.f,-2.f,2.f, -0.1f, 100.f);

    v3f scale = {1,1,1};
    v3f rot = {0};
    v3f trans = {0};
    trans.x = -0.3f;
    mat4x4f mat = {0};
    create_identity_matrix(&mat);
    create_srt(&mat, scale, rot, trans);

    unsigned int worldMat = glGetUniformLocation(shader_program, "uWorldMat");
    glUniformMatrix4fv(worldMat, 1, GL_FALSE, &mat.m11);

    unsigned int viewMat = glGetUniformLocation(shader_program, "uViewMat");
    glUniformMatrix4fv(viewMat, 1, GL_FALSE, &view.m11);

    render_single_mesh(&square);

    scale.y += 0.1f;
    scale.x -= 0.1f;
    trans.x  = 0.5f;
    create_srt(&mat, scale, rot, trans);

    glUniformMatrix4fv(worldMat, 1, GL_FALSE, &mat.m11);

    render_single_mesh(&triangle);
}
