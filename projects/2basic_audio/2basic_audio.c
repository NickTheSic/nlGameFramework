#include "nl_lib.h"

unsigned int song = 0;
unsigned int sfx = 0;

#ifdef PSP // TODO: Remove this from projects and place in the PSP input
#include <pspctrl.h>
#define key_space PSP_CTRL_CROSS
#define key_was_pressed(b) is_button_pressed(0, b)
#endif

static float volume = 0.75f;

void app_specific_init(void)
{
    song = load_sound_file("data/SneakySong.wav"); NL_LOG("Song Loaded");
    sfx = load_sound_file("data/run.wav");    NL_LOG("SFX Loaded");
    
    set_master_volume(volume);
    set_sound_to_loop(song);
    play_sound(song);
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);

    // Really rough scroll to change volume
    int v = get_mouse_scroll_this_frame();
    if (v != 0)
    {
        volume += v / 120.f;
        set_master_volume(volume);
    }

    if (key_was_pressed(key_a))
    {
        NL_LOG("Key Was Pressed");
        play_sound(sfx);
    }
}

void app_specific_render(void){}
void app_specific_cleanup(void){}