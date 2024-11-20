#include "nl_lib.h"

unsigned int song = 0;

void app_specific_init(void)
{
    song = load_sound_file("data/StS_Funeral.wav");
    set_sound_to_loop(song);
    play_sound(song);
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}

void app_specific_render(void)
{

}

void app_specific_cleanup(void)
{
    
}