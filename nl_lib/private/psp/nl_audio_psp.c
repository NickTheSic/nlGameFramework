#include "../nl_audio.h"
#include <pspaudiolib.h>
#include <pspaudio.h>

void audioCallback(void* buf, unsigned int length, void *userdata) 
{

}

int init_audio_system(void)
{
    pspAudioInit();
    pspAudioSetChannelCallback(0, audioCallback, NULL);
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
