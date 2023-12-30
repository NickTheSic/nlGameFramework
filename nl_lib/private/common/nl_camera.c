#include "../nl_camera.h"
#include "../nl_math.h"

void initialize_camera(camera* const cam, const v3f pos, const v2f size)
{
    cam->position.x = pos.x;
    cam->position.y = pos.y;
    cam->position.z = pos.z;
    cam->size.x = size.x;
    cam->size.y = size.y;

    recalculate_camera(cam);
}

void recalculate_camera_assuming_half_size(camera* const cam)
{
    create_orthographic_projection(
        &cam->matrix, 
        cam->position.x-cam->size.x, 
        cam->position.x+cam->size.x, 
        cam->position.y-cam->size.y, 
        cam->position.y+cam->size.y, 
        -0.1, 100
    );
}

void recalculate_camera_assuming_zero_to_size(camera* const cam)
{
    create_orthographic_projection(
        &cam->matrix, 
        cam->position.x, 
        cam->position.x + cam->size.x, 
        cam->position.y, 
        cam->position.y + cam->size.y, 
        -0.1, 100
        );
}

void recalculate_camera(camera* const cam)
{
    if (cam->assume_half_size == 1)
    {
        recalculate_camera_assuming_half_size(cam);
    }
    else
    {
        recalculate_camera_assuming_zero_to_size(cam);
    }
}
