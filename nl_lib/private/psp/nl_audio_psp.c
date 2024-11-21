#include "../nl_audio.h"
#include "../nl_debug.h"
#include "../nl_wave_file.h"
#include <pspaudiolib.h>
#include <pspaudio.h>

internal_function void channel_bgm(void* buf, unsigned int length, void *userdata) 
{
    NL_UNUSED(buf);
    NL_UNUSED(length);
    NL_UNUSED(userdata);
}

internal_function void channel_sfx(void* buf, unsigned int length, void *userdata) 
{
    NL_UNUSED(buf);
    NL_UNUSED(length);
    NL_UNUSED(userdata);
}

int init_audio_system(void)
{
    pspAudioInit();
    pspAudioSetChannelCallback(0, channel_bgm, NULL);
    pspAudioSetChannelCallback(1, channel_sfx, NULL);

    return 1;
}

void cleanup_audio_system(void)
{

}

unsigned int load_sound_file(const char* const filename)
{
    file_contents sound_file = {0};
    read_entire_file(filename, &sound_file);
    if (sound_file.size == 0)
    {
        NL_LOG("Unable to open sound file: %s", filename);
        return 0;
    }

    wav_file_header * const wav_header = (wav_file_header* const)(sound_file.content);
    NL_UNUSED(wav_header);
    const short channels = wav_header->channels;
    const short bits_per_sample = wav_header->bits_per_sample;
    const int data_size = wav_header->data_size;
    const int sample_rate = wav_header->sample_rate;

    pspAudioSetChannelCallback(0, channel_bgm, NULL);

    return 0;
}

void play_sound(unsigned int sound)
{
    NL_UNUSED(sound);
}

void set_sound_to_loop(unsigned int sound)
{
    NL_UNUSED(sound);
}
