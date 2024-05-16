#include "nl_lib.h"

unsigned int song_sound = 0;
unsigned int sfx_sound = 0;

void app_specific_init(void)
{
    song_sound = load_sound_file("data/StS_Funeral.wav");
    sfx_sound = load_sound_file("data/retrogamesfx.wav");

    play_sound(song_sound);
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
    
    if (was_key_pressed(key_space))
    {
        play_sound(sfx_sound);
    }
}

void app_specific_cleanup(void)
{
}
