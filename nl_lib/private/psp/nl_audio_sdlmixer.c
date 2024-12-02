#include "../nl_audio.h"
#include "../nl_debug.h"
#include <pspaudiolib.h>
#include <pspaudio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int init_audio_system(void)
{
    SDL_Init(SDL_INIT_AUDIO);

    // Initialize sdl2_mixer
    Mix_OpenAudio(44100, 
        MIX_DEFAULT_FORMAT, 
        MIX_DEFAULT_CHANNELS, 
        2048
    );
    return 1;
}

void cleanup_audio_system(void)
{

}

unsigned int load_sound_file(const char* const filename)
{
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

