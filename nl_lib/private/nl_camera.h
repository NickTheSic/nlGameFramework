#ifndef __NL_CAMERA_H__
#define __NL_CAMERA_H__
#include "nl_math.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct camera camera;
struct camera
{
    mat4x4f view_matrix; // Camera Postion, Orientation and Target
    mat4x4f proj_matrix; // Defines Orthographic or Projection
};

void initialize_camera_to_identity(camera* const cam);

void project_mouse_to_camera(camera* const cam, v2f* mouse_pos_on_screen);


#ifdef __cplusplus
}
#endif

#endif //__NL_CAMERA_H__