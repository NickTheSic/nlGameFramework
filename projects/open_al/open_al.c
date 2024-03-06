#include "nl_lib.h"

#include "include/al.h"
#include "include/alc.h"

ALCdevice *audio_device = {0};

extern void app_specific_init(void)
{
    audio_device = alcOpenDevice(0);
}

extern void app_specific_update(double dt)
{
    
}
