#ifndef __NL_RR_CAMERA_H__
#define __NL_RR_CAMERA_H__

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

    unsigned char transform_dirty : 1;
    unsigned char is_perspective : 1;
};

void initialize_rr_camera_to_default(nl_rr_camera* const camera);

// Just to contain the current size callback code into a specific function
void update_camera_view_from_size_callback(nl_rr_camera* const camera, float aspect_ratio);

void project_mouse_to_camera_view(const nl_rr_camera* const cam, v2f* const mouse_pos_on_screen);


#endif//__NL_RR_CAMERA_H__
