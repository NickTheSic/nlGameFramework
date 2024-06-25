#include "../nl_camera.h"
#include "../nl_math.h"

//camera main_camera = {0};

void initialize_camera_to_zero(camera* const cam)
{
    NL_UNUSED(cam);
    //create_identity_matrix(&cam->proj_matrix);
    //create_identity_matrix(&cam->view_matrix);
}

void project_mouse_to_camera(camera* const cam, v2f* mouse_pos_on_screen)
{
    mat4x4f inverse = {0};
    create_identity_matrix(&inverse);
    invert_matrix_4x4_glm(&cam->view_matrix, &inverse);

    v2f_mat4_transform(mouse_pos_on_screen, &inverse);
}
