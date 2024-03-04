#ifndef __NL_CAMERA_H__
#define __NL_CAMERA_H__
#include "nl_math.h"

typedef struct camera camera;
struct camera
{
    mat4x4f view_matrix;
    mat4x4f proj_matrix;
    
    v3f position;
    v2f size;
    v2f screen_size;

    float move_speed;
    int assume_half_size;
};

void create_screen_aspect(camera* const cam, int width, int height);

void recalculate_camera(camera* const cam);
void initialize_camera(camera* const cam, const v3f pos, const v2f size);
void update_camera_size(camera* const cam, float width, float height);
void update_camera(camera* const cam, float dt);

void create_perspective_vfov(float angle, float aspect, float near, float far);
void create_perspective_hfov(float angle, float aspect, float near, float far);

#endif //__NL_CAMERA_H__