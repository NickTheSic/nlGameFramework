#include "nl_lib.h"
#include "private/nl_gl.h"

#include "ui_batch_renderer.c"


static unsigned int square_indices[] =
{
    0,1,2,
    2,3,0
};
 
static ui_element square_ur = {0};
static ui_element square_bl = {0};
static ui_element square_center = {0};
static mesh mouse = {0};
static camera ui_camera = {0};
static ui_batch_renderer _ui_renderer = {0};

void init_mouse_mesh()
{
    const vertex_data _mouse_square[] =
    {
        {{-SQUARE_HALF_SIZE, -SQUARE_HALF_SIZE, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f}},
        {{ SQUARE_HALF_SIZE, -SQUARE_HALF_SIZE, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f}},
        {{ SQUARE_HALF_SIZE,  SQUARE_HALF_SIZE, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f}},
        {{-SQUARE_HALF_SIZE,  SQUARE_HALF_SIZE, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f}}
    };

    const unsigned int _indices[] =
    {
        0,1,2,
        2,3,0
    };

    generate_mesh_using_vertices_and_indices(&mouse, _mouse_square, 4, _indices, 6);
}


void matrix_for_ui(ui_element* const o)
{
    mat4x4f mat = {0};
    ui_anchored_matrix(&mat, o);

    unsigned int worldMat = glGetUniformLocation(shader_program, "uWorldMat");
    glUniformMatrix4fv(worldMat, 1, GL_FALSE, &mat.m11);

    add_element_to_ui_renderer(&_ui_renderer, o, &mat);
}

void winsizecbk(int width, int height)
{
    create_orthographic_projection(&ui_camera.view_matrix, 0, width, 0, height, -0.1f, 100.f);
    unsigned int viewMat = glGetUniformLocation(shader_program, "uViewMat");
    glUniformMatrix4fv(viewMat, 1, GL_FALSE, &ui_camera.view_matrix.m11);
}

void initialize_object(ui_element* o, v2f anchor)
{
    o->color = (colourf){1.0f,1.0f,1.0f,1.0f};

    o->anchor.x = anchor.x;
    o->anchor.y = anchor.y;

    initialize_transform2d(&o->trans);
}

void app_specific_init(void)
{
    init_mouse_mesh();

    initialize_object(&square_ur, (v2f){-1.0f,1.0f});
    square_ur.trans.position.x = SQUARE_HALF_SIZE;
    square_ur.trans.position.y = -SQUARE_HALF_SIZE;
    initialize_object(&square_bl, (v2f){1.0f,-1.0f});
    square_bl.trans.position.x = -SQUARE_HALF_SIZE;
    square_bl.trans.position.y = SQUARE_HALF_SIZE;
    initialize_object(&square_center, (v2f){0.0f,0.0f});

    initialize_ui_renderer(&_ui_renderer, (unsigned int)4);

    initialize_camera_to_zero(&ui_camera);
    pfn_window_size_callback = &winsizecbk;

    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);

    matrix_for_ui(&square_ur);
    matrix_for_ui(&square_bl);
    matrix_for_ui(&square_center);

    draw_ui_batch(&_ui_renderer);

    v2i cur_mouse_pos = get_mouse_position_from_system();
    v3f scale = {0.1,0.1,0.1};
    v3f rot = {0};
    v3f trans = {cur_mouse_pos.x, cur_mouse_pos.y, 0};
    mat4x4f mat = {0};
    create_identity_matrix(&mat);
    create_srt_matrix(&mat, scale, rot, trans);

    unsigned int worldMat = glGetUniformLocation(shader_program, "uWorldMat");
    glUniformMatrix4fv(worldMat, 1, GL_FALSE, &mat.m11);

    render_single_mesh(&mouse);
}

void app_specific_cleanup()
{
    free_mesh(&mouse);
    free_ui_batch_renderer(&_ui_renderer);
}
