#include "nl_lib.h"
#include "private/nl_gl.h"

nl_key rebinder = key_zero;
nl_key jump = key_space;

extern void app_specific_init(void)
{

}

extern void app_specific_update(double dt)
{
    if (is_key_held(rebinder))
    {
        NL_LOG("Rebinding");
        jump = get_last_key_pressed();
    }

    if (was_key_pressed(jump))
    {
        NL_LOG("Jumping!");
    }
}
