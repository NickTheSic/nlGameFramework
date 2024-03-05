#include "nl_lib.h"
#include "private/nl_gl.h"

#define SQUARE_HALF_SIZE 100.0f

static vertex_data square_verts[] =
{
    {{-SQUARE_HALF_SIZE, -SQUARE_HALF_SIZE, 0.0f}, {1.0f, 0.5f, 0.8f, 1.0f}},
    {{ SQUARE_HALF_SIZE, -SQUARE_HALF_SIZE, 0.0f}, {0.8f, 1.0f, 0.5f, 1.0f}},
    {{ SQUARE_HALF_SIZE,  SQUARE_HALF_SIZE, 0.0f}, {0.5f, 0.8f, 1.0f, 1.0f}},
    {{-SQUARE_HALF_SIZE,  SQUARE_HALF_SIZE, 0.0f}, {0.7f, 0.2f, 0.0f, 1.0f}}
};

static unsigned int square_indices[] =
{
    0,1,2,
    2,3,0
};

typedef struct ui_object object;
struct ui_object
{
    transform2d trans;
    v2f anchor;
    mesh m;
};

static object square_ur = {0};
static object square_bl = {0};
static object square_center = {0};
static object mouse = {0};
static camera ui_camera = {0};
static unsigned int shader_program = {0};

void winsizecbk(int width, int height)
{
    create_orthographic_projection(&ui_camera.view_matrix, 0, width, 0, height, -0.1f, 100.f);
    unsigned int viewMat = glGetUniformLocation(shader_program, "uViewMat");
    glUniformMatrix4fv(viewMat, 1, GL_FALSE, &ui_camera.view_matrix.m11);
}

void initialize_object(object* o, v2f anchor)
{
    generate_mesh_using_vertices_and_indices(&o->m, square_verts, 4, square_indices, 6);

    o->anchor.x = anchor.x;
    o->anchor.y = anchor.y;

    initialize_transform2d(&o->trans);
}

void app_specific_init(void)
{
    initialize_object(&square_ur, (v2f){-1.0f,1.0f});
    square_ur.trans.position.x = SQUARE_HALF_SIZE;
    square_ur.trans.position.y = -SQUARE_HALF_SIZE;
    initialize_object(&square_bl, (v2f){1.0f,-1.0f});
    square_bl.trans.position.x = -SQUARE_HALF_SIZE;
    square_bl.trans.position.y = SQUARE_HALF_SIZE;
    initialize_object(&square_center, (v2f){0.0f,0.0f});
    initialize_object(&mouse, (v2f){0.0f,0.0f});

    shader_program = create_shader_program(common_vert_shader_code, common_fragment_shader_code);
    use_shader_program(shader_program);

    initialize_camera_to_zero(&ui_camera);
    pfn_window_size_callback = &winsizecbk;

    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);
}

void ui_anchored_matrix(mat4x4f* const mat, object* const o)
{
    create_identity_matrix(mat);

    v2i screen_size = get_screen_size();
    transform2d trans = o->trans;
    float half_w = screen_size.x/2.0f;
    float half_h = screen_size.y/2.0f;
    trans.position.x += (half_w) + (o->anchor.x * half_w);
    trans.position.y += (half_h) + (o->anchor.y * half_h);
    create_srt_matrix_from_transform2d(mat, trans);
}

void matrix_for_ui(object* const o)
{
    mat4x4f mat = {0};
    ui_anchored_matrix(&mat, o);

    unsigned int worldMat = glGetUniformLocation(shader_program, "uWorldMat");
    glUniformMatrix4fv(worldMat, 1, GL_FALSE, &mat.m11);

    render_single_mesh(&o->m);
}

void app_specific_update(double dt)
{
    matrix_for_ui(&square_ur);
    matrix_for_ui(&square_bl);
    matrix_for_ui(&square_center);


    v2i cur_mouse_pos = get_mouse_position_from_system();
    v3f scale = {0.1,0.1,0.1};
    v3f rot = {0};
    v3f trans = {cur_mouse_pos.x, cur_mouse_pos.y, 0};
    mat4x4f mat = {0};
    create_identity_matrix(&mat);
    create_srt_matrix(&mat, scale, rot, trans);

    unsigned int worldMat = glGetUniformLocation(shader_program, "uWorldMat");
    glUniformMatrix4fv(worldMat, 1, GL_FALSE, &mat.m11);

    render_single_mesh(&mouse.m);
}
