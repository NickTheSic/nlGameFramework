#include "../nl_audio.h"
#include "../nl_debug.h"
#include "../nl_wave_file.h"
#include <pspaudiolib.h>
#include <pspaudio.h>

internal_function void channel_bgm(void* buf, unsigned int length, void *userdata) 
{

}

int init_audio_system(void)
{
    pspAudioInit();
    pspAudioSetChannelCallback(0, channel_bgm, NULL);
}

void cleanup_audio_system(void)
{

}

unsigned int load_sound_file(const char* const filename)
{

}

void play_sound(unsigned int sound)
{

}

void set_sound_to_loop(unsigned int sound)
{

}
