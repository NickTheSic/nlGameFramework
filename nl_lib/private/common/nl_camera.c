#include "../nl_camera.h"
#include "../nl_math.h"

void initialize_camera(camera* const cam, const v3f pos, const v2f size)
{
    cam->position.x = pos.x;
    cam->position.y = pos.y;
    cam->position.z = pos.z;
    cam->size.x = size.x;
    cam->size.y = size.y;

    cam->move_speed = size.y / 10.f;

    recalculate_camera(cam);
}

internal_function void recalculate_camera_assuming_half_size(camera* const cam)
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

internal_function void recalculate_camera_assuming_zero_to_size(camera* const cam)
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

void update_camera(camera* const cam, float dt)
{
    if (is_key_held(key_alt))
    {
        if (is_key_held(key_a))
        {
            cam->position.x -= cam->move_speed * dt;
        }
        
        if (is_key_held(key_d))
        {
            cam->position.x += cam->move_speed * dt;
        }
        
        if (is_key_held(key_w))
        {
            cam->position.y += cam->move_speed * dt;
        }
        
        if (is_key_held(key_s))
        {
            cam->position.y -= cam->move_speed * dt;
        }

        if (was_mouse_button_pressed(NL_MOUSE_BUTTON_LEFT))
        {
            cam->assume_half_size = (cam->assume_half_size ^ 0b1);
        }

        const int mouse_frame_scroll = get_mouse_scroll_this_frame();
        cam->size.x += mouse_frame_scroll * 100 * dt;
        cam->size.y += mouse_frame_scroll * 100 * dt;

        recalculate_camera(cam);
    }
}
