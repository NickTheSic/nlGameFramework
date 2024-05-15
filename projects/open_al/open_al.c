#include "nl_lib.h"

#include "include/al.h"
#include "include/alc.h"

ALCdevice *audio_device = {0};
ALCcontext *audio_context = {0};

#define MAX_SOUND_BUFFERS 3
ALuint *sound_buffers = {0}

static void print_audio_device_name(void)
{
    const ALCchar* name = 0;
    if (alcIsExtensionPresent(audio_device, "ALC_ENUMERATE_ALL_EXT"))
    {
        name = alcGetString(audio_device, ALC_ALL_DEVICES_SPECIFIER);
    }
    if (!name || alcGetError(audio_device) != ALC_NO_ERROR)
    {
        name = alcGetString(audio_device, ALC_DEVICE_SPECIFIER);
    }
    NL_LOG("Opened %s", name);
}

static void load_sound(const char* filename)
{
    
}

void app_specific_init(void)
{
    audio_device = alcOpenDevice(0);
    if (audio_device == 0)
    {
        NL_LOG("Unable to create audio device");
    }
    
    audio_context = alcCreateContext(audio_device, 0);
    if (audio_context == 0)
    {
        NL_LOG("Unable to create audio context");
    }

    if (!alcMakeContextCurrent(audio_context))
    {
        NL_LOG("Unable to make audio context current");
    }
    print_audio_device_name();

}

void app_specific_update(double dt)
{
}

void app_specific_cleanup(void)
{
    alDeleteBuffers(MAX_SOUND_BUFFERS, sound_buffers);
}
