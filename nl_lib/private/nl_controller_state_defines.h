#ifndef __NL_CONTROLLER_STATE_DEFINES_H__
#define __NL_CONTROLLER_STATE_DEFINES_H__

// This is for tightly packing input structs together, mainly to be used for controllers
#define GENERATE_BUTTON_STATE_VARIABLES(name)\
    unsigned char name##_held       : 1;\
    unsigned char name##_pressed    : 1;\
    unsigned char name##_released   : 1;\
    unsigned char name##_down_state : 1;\
    unsigned char name##_prev_state : 1;


// based off of my input handling
#define GENERATE_UPDATE_STATE(var, sys_buttons, controller_button, my_button)\
    var.my_button##_down_state = (sys_buttons & controller_button) != 0;\
    var.my_button##_pressed = 0;\
    var.my_button##_released = 0;\
    if (var.my_button##_down_state != var.my_button##_prev_state)\
    {\
        if(var.my_button##_down_state)\
        {\
            var.my_button##_pressed = (var.my_button##_held == 0);\
            var.my_button##_held = 1;\
        }\
        else\
        {\
            var.my_button##_released = 1;\
            var.my_button##_held = 0;\
        }\
    }\
    var.my_button##_prev_state = var.my_button##_down_state;

#endif//__NL_CONTROLLER_STATE_DEFINES_H__