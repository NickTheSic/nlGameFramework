#ifndef __NL_UI_H__
#define __NL_UI_H__

#include "nl_mesh.h"

#ifdef __cplusplus
extern "C" {
#endif

//! Temporary
#define SQUARE_HALF_SIZE 100.0f
static vertex_data square_verts[] =
{
    {{-SQUARE_HALF_SIZE, -SQUARE_HALF_SIZE, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
    {{ SQUARE_HALF_SIZE, -SQUARE_HALF_SIZE, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
    {{ SQUARE_HALF_SIZE,  SQUARE_HALF_SIZE, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
    {{-SQUARE_HALF_SIZE,  SQUARE_HALF_SIZE, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}
};
static unsigned int square_indices[] =
{
    0,1,2,
    2,3,0
};

//!

typedef struct ui_element ui_element;
struct ui_element
{
    transform2d transform;
    v2f anchor;
    mesh m;
};

//! Temporary
void initialize_object(ui_element* o, v2f anchor);
//!

//* Could move this sort of class into the shader itself?
typedef struct nl_ui_shader nl_ui_shader;
struct nl_ui_shader
{
    unsigned int shader_program;
    unsigned int u_view_matrix;
    unsigned int u_world_matrix;
};

typedef struct nl_ui nl_ui;
struct nl_ui
{
    struct nl_sprite_sheet* sprite_atlas;
    nl_ui_shader shader_data;

    camera ui_camera;

    ui_element* elements;
    unsigned int elements_max;
    unsigned int elements_count;
};

int ui_init(/*Element count, amount of sprite texutes*/);
void ui_render();
void ui_cleanup();

void ui_set_window_size(int width, int height);
void ui_set_world_matrix(const float* const matrix_11);

#ifdef __cplusplus
}
#endif

#endif//__NL_UI_H__