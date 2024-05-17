#include "nl_lib.h"
#include "private/nl_gl.h"

//
#include "sprite_renderer.h"
#include "sprite_renderer.c"


static const char* vertex_shader_code =
NL_SHADER_VERSION_HEADER
"layout (location = 0) in vec3 aPos;                   \n"
"layout (location = 1) in vec4 aColor;                 \n"
"uniform mat4 uProjMat;                                \n"
"out vec4 oColor;                                      \n"
"void main() {                                         \n"
"   gl_Position = uProjMat * vec4(aPos,1.0);           \n"
"   oColor = aColor;                                   \n"
"}                                                     \0";

static const char* fragment_shader_code =
NL_SHADER_VERSION_HEADER
"out vec4 FragColor;                                   \n"
"in vec4 oColor;                                       \n"
"void main() {                                         \n"
"    FragColor = oColor;                               \n"
"}                                                     \0";

mesh player = {0};
unsigned int shader_program = 0;
camera main_cam = {0};

void winsizecbk(int width, int height)
{
    create_orthographic_projection(&main_cam.proj_matrix, 0, width, 0, height, -0.1f, 100.f);
    unsigned int projMat = glGetUniformLocation(shader_program, "uProjMat");
    glUniformMatrix4fv(projMat, 1, GL_FALSE, &main_cam.proj_matrix.m11);
}

void app_specific_init(void)
{
    generate_square_mesh(&player, 100, (colourf){1.0f,0.5f,0.2f,1.0f});

    shader_program = create_shader_program(vertex_shader_code, fragment_shader_code);
    use_shader_program(shader_program);

    pfn_window_size_callback = &winsizecbk;
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);
}

void app_specific_update(double dt)
{
    (void)dt;
}

void app_specific_render(void)
{
    render_single_mesh(&player);
}

void app_specific_cleanup(void)
{
    free_mesh(&player);
}