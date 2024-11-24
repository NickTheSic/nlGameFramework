#include "movement.h"

#if defined (__EMSCRIPTEN__) || defined (_WIN32)
#include <private/nl_input.h>
#endif

#if defined (PLATFORM_CONSOLE) || defined (_WIN32)
#include <private/nl_gamepad.h>
#endif

float get_movement_x()
{
    float movement = 0;

#if defined (__EMSCRIPTEN__) || defined (_WIN32)
    if (key_is_held(key_a))
    {
        movement -= 1.0f;
    }

    if (key_is_held(key_d))
    {
        movement += 1.0f;
    }
#endif

#if defined (PLATFORM_CONSOLE) || defined (_WIN32)
    if (is_button_pressed(0, NL_GAMEPAD_DPAD_LEFT))
    {
        movement -= 1.0f;
    }
    if (is_button_pressed(0, NL_GAMEPAD_DPAD_RIGHT))
    {
        movement += 1.0f;
    }
#endif

    return movement;
}

float get_movement_y()
{
    float movement = 0;
    

#if defined (__EMSCRIPTEN__) || defined (_WIN32)
    if (key_is_held(key_s))
    {
        movement -= 1.0f;
    }

    if (key_is_held(key_w))
    {
        movement += 1.0f;
    }
#endif

#if defined (PLATFORM_CONSOLE) || defined (_WIN32)
    if (is_button_pressed(0, NL_GAMEPAD_DPAD_DOWN))
    {
        movement -= 1.0f;
    }
    if (is_button_pressed(0, NL_GAMEPAD_DPAD_UP))
    {
        movement += 1.0f;
    }
#endif

    return movement;
}

