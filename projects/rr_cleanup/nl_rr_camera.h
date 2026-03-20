#ifndef __NL_RR_CAMERA_H__
#define __NL_RR_CAMERA_H__

typedef struct nl_rr_camera_controls nl_rr_camera_controls;
struct nl_rr_camera_controls
{
    nl_key up;
    nl_key down;
    nl_key left;
    nl_key right;
};

typedef struct nl_rr_camera nl_rr_camera;
struct nl_rr_camera
{
    mat4x4f view_matrix;
    mat4x4f proj_matrix;

    v3f position;
    v3f scale;
    v3f rotation;
    
    float near_z;
    float far_z;
    float aspect_ratio;

    nl_rr_camera_controls controls;

    unsigned char transform_dirty : 1;
    unsigned char is_perspective : 1;
};

void initialize_rr_camera_to_default(nl_rr_camera* const camera);
void update_camera(nl_rr_camera* const camera, double dt);
void setup_camera_matrices(nl_rr_camera* const camera);

void project_mouse_to_camera_view(const nl_rr_camera* const cam, v2f* const mouse_pos_on_screen);


#endif//__NL_RR_CAMERA_H__
