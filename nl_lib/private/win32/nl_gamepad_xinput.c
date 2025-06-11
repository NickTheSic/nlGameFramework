#include "../nl_gamepad.h"
#include <xinput.h>

typedef struct gamepad_button_state gamepad_button_state;
struct gamepad_button_state
{
    unsigned char held       : 1;
    unsigned char pressed    : 1;
    unsigned char released   : 1;
    unsigned char down_state : 1;
    unsigned char prev_state : 1;
    unsigned char pad        : 3; // explicit padding
};

typedef struct win_gamepad win_gamepad;
struct win_gamepad
{
    float left_trigger, right_trigger;
    float left_x_axis, left_y_axis;
    float right_x_axis, right_y_axis;

    union
    {
        gamepad_button_state buttons[14];
        struct 
        {
            gamepad_button_state dpad_up;
            gamepad_button_state dpad_down;
            gamepad_button_state dpad_left;
            gamepad_button_state dpad_right;
            gamepad_button_state start;
            gamepad_button_state select;
            gamepad_button_state left_stick;
            gamepad_button_state right_stick; 
            gamepad_button_state left_shoulder;
            gamepad_button_state right_shoulder;
            gamepad_button_state a;
            gamepad_button_state b;
            gamepad_button_state x;
            gamepad_button_state y;
        };
    };
};
global_variable win_gamepad win_controller = {0}; 

#define X_INPUT_GET_STATE(name) DWORD name(DWORD ControllerNumber, XINPUT_STATE* State)
typedef X_INPUT_GET_STATE(x_input_get_state);
X_INPUT_GET_STATE(XInputGetStateStub)
{
    NL_UNUSED(ControllerNumber); NL_UNUSED(State)
    NL_LOG("XInput Get State Stub");
    return 0;
}
x_input_get_state *XInputGetState_ = XInputGetStateStub;
#define XInputGetState XInputGetState_

#define X_INPUT_SET_STATE(name) DWORD name(DWORD ControllerNumber, XINPUT_VIBRATION* Vibration)
typedef X_INPUT_SET_STATE(x_input_set_state);
X_INPUT_SET_STATE(XInputSetStateStub)
{
    NL_UNUSED(ControllerNumber); NL_UNUSED(Vibration);
    NL_LOG("XInput Set State Stub");
    return 0;
}
x_input_set_state *XInputSetState_ = XInputSetStateStub;
#define XInputSetState XInputSetState_

HMODULE XInputLibrary = {0};

int init_gamepad_system(void)
{
    XInputLibrary = LoadLibrary("xinput1_4.dll");

    if (!XInputLibrary)
    {
        XInputLibrary = LoadLibrary("xinput1_3.dll");
        if (!XInputLibrary)
        {
            XInputLibrary = LoadLibrary("Xinput9_1_0.dll");
            if (XInputLibrary)
            {
                NL_LOG("Using xinput 9_1_0");
            }
        } else {
            NL_LOG("Using xinput1_3");
        }
    } else {
        NL_LOG("Using xinput1_4");
    }

    if (XInputLibrary)
    {
        XInputGetState = (x_input_get_state*)GetProcAddress(XInputLibrary, "XInputGetState");
        if (XInputGetState == 0)
        {
            NL_LOG("Failed to retrive XInputGetState. XInputGetState will use the stub");
            XInputGetState = XInputGetStateStub;
        }
        XInputSetState = (x_input_set_state*)GetProcAddress(XInputLibrary, "XInputSetState");
        if (XInputSetState == 0)
        {
            NL_LOG("Failed to retrive XInputSetState. XInputSetState will use the stub");
            XInputSetState = XInputSetStateStub;
        }
    }
    else
    {
        NL_LOG("XInput was not found on this system.  Unable to initialize gamepad system");
        return 0;
    }

    return 1;
}

void cleanup_gamepad_system(void)
{
    FreeLibrary(XInputLibrary);
}

#define UPDATE_XINPUT_GAMEPAD_BUTTON_STATE(my_button, xinput_button)\
{\
win_controller.my_button.down_state = (pad->wButtons & xinput_button) != 0;\
win_controller.my_button.pressed    = 0;\
win_controller.my_button.released   = 0;\
    if (win_controller.my_button.down_state != win_controller.my_button.prev_state)\
    {\
        if(win_controller.my_button.down_state)\
        {\
            win_controller.my_button.pressed = (win_controller.my_button.held == 0);\
            win_controller.my_button.held = 1;\
        }\
        else\
        {\
            win_controller.my_button.released = 1;\
            win_controller.my_button.held = 0;\
        }\
    }\
win_controller.my_button.prev_state = win_controller.my_button.down_state;\
}

void udpate_gamepad(void)
{
    XINPUT_STATE state = {0};
    if (XInputGetState(0, &state) == 0)
    {   
        const XINPUT_GAMEPAD* const pad = &state.Gamepad;
        UPDATE_XINPUT_GAMEPAD_BUTTON_STATE(dpad_up, XINPUT_GAMEPAD_DPAD_UP);
        UPDATE_XINPUT_GAMEPAD_BUTTON_STATE(dpad_down, XINPUT_GAMEPAD_DPAD_DOWN);
        UPDATE_XINPUT_GAMEPAD_BUTTON_STATE(dpad_left, XINPUT_GAMEPAD_DPAD_LEFT);
        UPDATE_XINPUT_GAMEPAD_BUTTON_STATE(dpad_right, XINPUT_GAMEPAD_DPAD_RIGHT);
        UPDATE_XINPUT_GAMEPAD_BUTTON_STATE(start, XINPUT_GAMEPAD_START);
        UPDATE_XINPUT_GAMEPAD_BUTTON_STATE(select, XINPUT_GAMEPAD_BACK);
        UPDATE_XINPUT_GAMEPAD_BUTTON_STATE(left_stick, XINPUT_GAMEPAD_LEFT_THUMB);
        UPDATE_XINPUT_GAMEPAD_BUTTON_STATE(right_stick, XINPUT_GAMEPAD_RIGHT_THUMB);
        UPDATE_XINPUT_GAMEPAD_BUTTON_STATE(left_shoulder, XINPUT_GAMEPAD_LEFT_SHOULDER);
        UPDATE_XINPUT_GAMEPAD_BUTTON_STATE(right_shoulder, XINPUT_GAMEPAD_RIGHT_SHOULDER);
        UPDATE_XINPUT_GAMEPAD_BUTTON_STATE(a, XINPUT_GAMEPAD_A);
        UPDATE_XINPUT_GAMEPAD_BUTTON_STATE(b, XINPUT_GAMEPAD_B);
        UPDATE_XINPUT_GAMEPAD_BUTTON_STATE(x, XINPUT_GAMEPAD_X);
        UPDATE_XINPUT_GAMEPAD_BUTTON_STATE(y, XINPUT_GAMEPAD_Y);

        win_controller.left_trigger   = (float)pad->bLeftTrigger / 255.f;
        win_controller.right_trigger  = (float)pad->bRightTrigger / 255.f;

        if (pad->sThumbLX < 0)
        {
            win_controller.left_x_axis = (float)pad->sThumbLX / 32768.0f;
        } 
        else 
        {
            win_controller.left_x_axis = (float)pad->sThumbLX / 32767.0f;
        }

        if (pad->sThumbLY < 0)
        {
            win_controller.left_y_axis = (float)pad->sThumbLY / 32768.f;
        } 
        else 
        {   
            win_controller.left_y_axis = (float)pad->sThumbLY / 32767.f;
        }   

        if (pad->sThumbRX < 0)
        {
            win_controller.right_x_axis = (float)pad->sThumbRX / 32768.f;
        } 
        else 
        {
            win_controller.right_x_axis = (float)pad->sThumbRX / 32767.f;
        }

        if (pad->sThumbRY < 0)
        {
            win_controller.right_y_axis = (float)pad->sThumbRY / 32768.f;
        } 
        else 
        {
            win_controller.right_y_axis = (float)pad->sThumbRY / 32767.f;
        }
    }      
}

int get_pressed_buttons(void)
{
    XINPUT_STATE state = {0};

    if (XInputGetState(0, &state) == 0)
    {
        return state.Gamepad.wButtons;
    }

    return 0;
}

unsigned char button_is_held(button_value_type button)
{
    return win_controller.buttons[button].held;
}

// Incorrectly setup - Controller only handles if it is held, this wants to know if it was pressed this frame
unsigned char button_was_pressed(button_value_type button)
{
    return win_controller.buttons[button].pressed;
}

unsigned char button_was_released(button_value_type button)
{
    return win_controller.buttons[button].released;
}

#define PRINT_BUTTON_PRESS_RELEASE(button)\
{if (button_was_pressed(button)){NL_LOG(#button" pressed");}\
else if (button_was_released(button)){NL_LOG(#button" pressed");}}

void debug_test_controller(void)
{
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_DPAD_UP     );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_DPAD_DOWN   );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_DPAD_LEFT   );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_DPAD_RIGHT  );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_START       );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_SELECT      );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_L           );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_R           );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_LEFT_THUMB  );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_RIGHT_THUMB );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_A           );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_B           );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_X           );
    PRINT_BUTTON_PRESS_RELEASE(NL_GAMEPAD_Y           );
}
