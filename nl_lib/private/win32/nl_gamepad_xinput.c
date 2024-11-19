#include "../nl_gamepad.h"

#include <xinput.h>

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
    NL_UNIMPLEMENTED_FUNC;
}

int get_pressed_buttons(int button)
{
    NL_UNIMPLEMENTED_FUNC;
    return 0;
}

int is_button_pressed(int button)
{
    NL_UNIMPLEMENTED_FUNC;
    return 0;
}
