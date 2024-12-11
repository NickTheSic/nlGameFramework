#include "nl_lib.h"

unsigned int song = 0;
unsigned int sfx = 0;

#ifdef PSP
#include <pspctrl.h>
#define key_space PSP_CTRL_CROSS
#define key_was_pressed(b) is_button_pressed(0, b)
#endif

void app_specific_init(void)
{
    song = load_sound_file("data/SneakySong.wav");
    NL_LOG("Song Loaded");
    sfx = load_sound_file("data/laserHit.wav");
    NL_LOG("SFX Loaded");

    set_sound_to_loop(song);
    play_sound(song);
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);

    if (key_was_pressed(key_space))
    {
        NL_LOG("Key Was Pressed");
        play_sound(sfx);
    }
}

void app_specific_render(void)
{

}

void app_specific_cleanup(void)
{
    
}