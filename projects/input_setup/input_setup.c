#include "nl_lib.h"
#include "private/nl_gl.h"

typedef void (*PFN_AxisInputBinding)(float value);

PFN_AxisInputBinding HorizontalMovement = {0};
PFN_AxisInputBinding VerticalMovement   = {0};

void app_specific_init(void)
{

}

void app_specific_update(double dt)
{

}

void app_specific_cleanup()
{

}