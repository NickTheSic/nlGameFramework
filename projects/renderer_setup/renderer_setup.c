#include "nl_lib.h"
#include "private/nl_gl.h"

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
    {{-100.5f, -100.5f, 5.0f}, {1.0f, 0.5f, 0.8f, 1.0f}},
    {{ 100.5f, -100.5f, 0.0f}, {0.8f, 1.0f, 0.5f, 1.0f}},
    {{ 100.5f,  100.5f, -5.0f}, {0.5f, 0.8f, 1.0f, 1.0f}},
    {{-100.5f,  100.5f, 0.0f}, {0.7f, 0.2f, 0.0f, 1.0f}}
};

unsigned int square_indices[] =
{
    0,1,2,
    2,3,0
};

// Required - Could be renderer or material
unsigned int shader_program;

void winsizecbk(int width, int height)
{
    //float aspect = (float)width/(float)height;  
    //create_orthographic_projection(&main_camera.proj_matrix, -1 * aspect, aspect, -1, 1, -0.1f, 100.f);

    create_orthographic_projection(&main_camera.view_matrix, -width, width, -height, height, -0.1f, 100.f);
    unsigned int viewMat = glGetUniformLocation(shader_program, "uViewMat");
    glUniformMatrix4fv(viewMat, 1, GL_FALSE, &main_camera.view_matrix.m11);
}

void app_specific_init(void)
{
    NL_LOG("Startup!");
    
    pfn_window_size_callback = & winsizecbk;
    generate_mesh_using_vertices_and_indices(&triangle, vertices, 3, square_indices, 3);
    generate_mesh_using_vertices_and_indices(&square, square_verts, 4, square_indices, 6);
    
    shader_program = create_shader_program(common_vert_shader_code, common_fragment_shader_code);
    use_shader_program(shader_program);
    
    initialize_camera_to_zero(&main_camera);

    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);
}

static v2f mouse_pos = {0};
static v2i cur_mouse_pos = {0};
static v2f screen_pos = {0};

void app_specific_update(double dt)
{
    (void)dt;

    cur_mouse_pos = get_mouse_position_from_system();
    if (mouse_pos.x != cur_mouse_pos.x || mouse_pos.y != cur_mouse_pos.y)
    {
        mouse_pos.x = (float)cur_mouse_pos.x;
        mouse_pos.y = (float)cur_mouse_pos.y;
 
        screen_pos.x = (float)mouse_pos.x;
        screen_pos.y = (float)mouse_pos.y;

        NL_LOG("New Mouse Pos X: %f, Y: %f", screen_pos.x, screen_pos.y);
    }
    
    use_shader_program(shader_program);

    v3f scale = {1,1,1};
    v3f rot = {0};
    v3f trans = {screen_pos.x, screen_pos.y, 0};
    mat4x4f mat = {0};
    create_identity_matrix(&mat);
    create_srt_matrix(&mat, scale, rot, trans);

    unsigned int worldMat = glGetUniformLocation(shader_program, "uWorldMat");
    glUniformMatrix4fv(worldMat, 1, GL_FALSE, &mat.m11);
    render_single_mesh(&square);
    render_single_mesh(&triangle);
}
