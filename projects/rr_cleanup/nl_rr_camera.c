#include "nl_rr_camera.h"

/*
struct nl_rr_camera
{
    mat4x4f view_matrix;
    mat4x4f projection_matrix;

    v3f position;
    v3f scale;
    v3f rotation;
    
    float near_z;
    float far_z;

    unsigned char transform_dirty : 1;
    unsigned char is_perspective : 1;
};
*/

void initialize_rr_camera_to_default(nl_rr_camera* const camera)
{
    create_identity_matrix(&camera->view_matrix);
    create_identity_matrix(&camera->proj_matrix);

    camera->position = (v3f){0.0f,0.0f,0.0f};
    camera->scale = (v3f){1.0f,1.0f,1.0f};
    camera->rotation = (v3f){0.0f,0.0f,0.0f};

    camera->near_z = 0.0f;
    camera->far_z = 500.0f;

    camera->aspect_ratio = 1.0f;

    camera->transform_dirty = 0;
    camera->is_perspective = 0;

    camera->controls = (nl_rr_camera_controls){key_w, key_s, key_a, key_d};
}

void project_mouse_to_camera_view(const nl_rr_camera* const camera, v2f* const mouse_pos_on_screen)
{
    mat4x4f inverse = {0};
    
    create_identity_matrix(&inverse);
    invert_matrix_4x4_glm(&camera->view_matrix, &inverse);

    v2f_mat4_transform(mouse_pos_on_screen, &inverse);
}

void update_camera(nl_rr_camera* const camera, double dt)
{
    main_camera.rotation.y += 50 * dt;
    main_camera.transform_dirty = 1;

    if (mouse_button_was_pressed(NL_MOUSE_BUTTON_LEFT))
    {
        main_camera.is_perspective = !main_camera.is_perspective;
        v2i screen_size = get_screen_size();
        winsizecbk(screen_size.x, screen_size.y);
    }

    int move_delta = get_mouse_scroll_this_frame();
    if (0 != move_delta)
    {
        main_camera.position.z +=  4.0f * -move_delta * dt;
        main_camera.transform_dirty = 1;
    }

    if (mouse_button_is_held(NL_MOUSE_BUTTON_RIGHT))
    {
        int move_delta = get_mouse_movement_this_frame().y;
        if (0 != move_delta)
        {
            main_camera.position.z +=  220.0f * move_delta * dt;
            main_camera.transform_dirty = 1;
        }
    }

    // These controls do not take rotation into account and that is fine for now

    if (key_is_held(camera->controls.up))
    {
        main_camera.position.y -= 120.f * dt;
        main_camera.transform_dirty = 1;
    }
    else if (key_is_held(camera->controls.down))
    {
        main_camera.position.y += 120.f * dt;
        main_camera.transform_dirty = 1;
    }

    if (key_is_held(camera->controls.right))
    {
        main_camera.position.x -= 120.f * dt;
        main_camera.transform_dirty = 1;
    }
    else if (key_is_held(camera->controls.left))
    {
        main_camera.position.x += 120.f * dt;
        main_camera.transform_dirty = 1;
    }
}

void setup_camera_matrices(nl_rr_camera* const camera)
{
    if (0 == camera->transform_dirty)
    {
        return;
    }

    camera->transform_dirty = 0;

    unsigned int view_loc = get_uniform_loc(rr_shader_program, "uViewMatrix");
    unsigned int proj_loc = get_uniform_loc(rr_shader_program, "uProjection");
    
    create_srt_matrix(&camera->view_matrix, camera->scale, camera->rotation, camera->position);

    if (0 == camera->is_perspective) 
    {
        const float camera_z = camera->position.z;
        const float w_size = camera->aspect_ratio*camera_z;
        create_orthographic_projection(&camera->proj_matrix, -w_size, w_size, -camera_z, camera_z, camera->near_z, camera->far_z);
    } 
    else 
    {
        create_perspective_projection(&camera->proj_matrix, 90.f, camera->aspect_ratio, camera->near_z, camera->far_z);
    }
    
    set_uniform_mat4x4f(proj_loc, &camera->proj_matrix.m11);
    set_uniform_mat4x4f(view_loc, &camera->view_matrix.m11);
}

