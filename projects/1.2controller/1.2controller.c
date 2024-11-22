#include "nl_lib.h"

// if control is pressed and released seems like my favourite way
// game pad is super easy it seems, just define the buttons for each platform
// I'll start there

#define NL_CONTROL_TYPE_KEYBOARD   0x01
#define NL_CONTROL_TYPE_MOUSE      0x02
#define NL_CONTROL_TYPE_CONTROLLRE 0x04

// 

typedef void (*PFNCONTROLINPUTCALLBACK)();

internal_function set_keyboard_callback(PFNCONTROLINPUTCALLBACK callback, nl_key key)
{

}

internal_function set_control_callback(unsigned char type, PFNCONTROLINPUTCALLBACK callback, unsigned int input_value)
{
    switch (type)
    {
        case NL_CONTROL_TYPE_KEYBOARD:
        {   
            set_keyboard_callback(callback, (nl_key)input_value);
        }break;
    }
}

void app_specific_init(void)
{

}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}

void app_specific_render(void)
{

}

void app_specific_cleanup(void)
{
    
}