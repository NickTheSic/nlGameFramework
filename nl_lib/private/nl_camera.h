#ifndef __NL_CAMERA_H__
#define __NL_CAMERA_H__
#include "nl_math.h"

typedef struct camera camera;
struct camera
{
    mat4x4f matrix;
    
    v3f position;
    v2f size;

    float move_speed;
    int assume_half_size;
};

void recalculate_camera(camera* const cam);
void initialize_camera(camera* const cam, const v3f pos, const v2f size);
void update_camera_size(camera* const cam, float width, float height);
void update_camera(camera* const cam, float dt);

#endif //__NL_CAMERA_H__