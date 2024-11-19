#include "../nl_gamepad.h"

#include <xinput.h>

typedef struct win_gamepad win_gamepad;
struct win_gamepad
{
    float left_trigger, right_trigger;
    float left_x_axis, left_y_axis;
    float right_x_axis, right_y_axis;

    union
    {
        struct 
        {
            unsigned short dpad_up        : 1;
            unsigned short dpad_down      : 1;
            unsigned short dpad_left      : 1;
            unsigned short dpad_right     : 1;
            unsigned short start          : 1;
            unsigned short select         : 1;
            unsigned short left_stick     : 1;
            unsigned short right_stick    : 1; 
            unsigned short left_shoulder  : 1;
            unsigned short right_shoulder : 1;
            unsigned short a              : 1;
            unsigned short b              : 1;
            unsigned short x              : 1;
            unsigned short y              : 1;
            unsigned short pad : 2; //explicit padding
        };
        unsigned short buttons;
    };
};

global_variable win_gamepad controllers[MAX_PLAYERS] = {0}; 

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
        }
    }

    if (XInputLibrary)
    {
        XInputGetState = (x_input_get_state*)GetProcAddress(XInputLibrary, "XInputGetState");
        XInputSetState = (x_input_set_state*)GetProcAddress(XInputLibrary, "XInputSetState");
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

void udpate_gamepad(void)
{
    for (int i=0; i<MAX_PLAYERS; i++)
    {
        XINPUT_STATE state = {0};
        if (XInputGetState(i, &state) == 0)
        {   
            XINPUT_GAMEPAD* pad = &state.Gamepad;

            controllers[i].dpad_up        = (pad->wButtons & XINPUT_GAMEPAD_DPAD_UP)        != 0;
            controllers[i].dpad_down      = (pad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN)      != 0;
            controllers[i].dpad_left      = (pad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT)      != 0;
            controllers[i].dpad_right     = (pad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)     != 0;
            controllers[i].start          = (pad->wButtons & XINPUT_GAMEPAD_START)          != 0;
            controllers[i].select         = (pad->wButtons & XINPUT_GAMEPAD_BACK)           != 0;
            controllers[i].left_stick     = (pad->wButtons & XINPUT_GAMEPAD_LEFT_THUMB)     != 0;
            controllers[i].right_stick    = (pad->wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)    != 0;
            controllers[i].left_shoulder  = (pad->wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)  != 0;
            controllers[i].right_shoulder = (pad->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) != 0;
            controllers[i].a              = (pad->wButtons & XINPUT_GAMEPAD_A)              != 0;
            controllers[i].b              = (pad->wButtons & XINPUT_GAMEPAD_B)              != 0;
            controllers[i].x              = (pad->wButtons & XINPUT_GAMEPAD_X)              != 0;
            controllers[i].y              = (pad->wButtons & XINPUT_GAMEPAD_Y)              != 0;

            controllers[i].left_trigger   = (float)pad->bLeftTrigger / 255.f;
            controllers[i].right_trigger  = (float)pad->bRightTrigger / 255.f;

            if (pad->sThumbLX < 0)
            {
                controllers[i].left_x_axis = (float)pad->sThumbLX / 32768.0f;
            } 
            else 
            {
                controllers[i].left_x_axis = (float)pad->sThumbLX / 32767.0f;
            }

            if (pad->sThumbLY < 0)
            {
                controllers[i].left_y_axis = (float)pad->sThumbLY / 32768.f;
            } 
            else 
            {   
                controllers[i].left_y_axis = (float)pad->sThumbLY / 32767.f;
            }   

            if (pad->sThumbRX < 0)
            {
                controllers[i].right_x_axis = (float)pad->sThumbRX / 32768.f;
            } 
            else 
            {
                controllers[i].right_x_axis = (float)pad->sThumbRX / 32767.f;
            }

            if (pad->sThumbRY < 0)
            {
                controllers[i].right_y_axis = (float)pad->sThumbRY / 32768.f;
            } 
            else 
            {
                controllers[i].right_y_axis = (float)pad->sThumbRY / 32767.f;
            }
        }
    }
}

int get_pressed_buttons(int controller_index)
{
    return controllers[controller_index].buttons;
}

int is_button_pressed(unsigned char controller_index, int button)
{
    return controllers[controller_index].buttons & button;
}
