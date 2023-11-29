#include "nl_lib.h"
#include "private/nl_gl.h"

global_variable nl_key rebinder = key_zero;
global_variable nl_key jump = key_space;

typedef struct input_action input_action;
struct input_action
{
    
}

extern void app_specific_init(void)
{

}

extern void app_specific_update(double dt)
{
    if (was_key_pressed(rebinder))
    {
        NL_LOG("Rebinding");
        jump = get_last_key_pressed();
    }

    if (was_key_pressed(jump))
    {
        NL_LOG("Jumping!");
    }
}
