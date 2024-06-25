#ifndef __NL_CAMERA_H__
#define __NL_CAMERA_H__
#include "nl_math.h"

typedef struct camera camera;
struct camera
{
    mat4x4f view_matrix; // Camera Psotion, Orientation and Target
    mat4x4f proj_matrix; // Defines Orthographic or Projection
};

void initialize_camera_to_zero(camera* const cam);

void project_mouse_to_camera(camera* const cam, v2f* mouse_pos_on_screen);

#endif //__NL_CAMERA_H__