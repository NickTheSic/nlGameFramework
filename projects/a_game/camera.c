#include "nl_lib.h"

typedef struct camera camera;
struct camera
{
    mat4x4f matrix;
    
    v3f position;
    v2f size;
};

internal_function void recalculate_camera(camera* const cam)
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

internal_function void initialize_orthographic_camera(camera* const cam, v2f size)
{
    cam->size.x = size.x;
    cam->size.y = size.y;

    recalculate_camera(cam);
}
