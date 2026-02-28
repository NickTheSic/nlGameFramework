#include "nl_lib.h"

#include "nl_mesh.h"
#include "nl_sprite_atlas.h"
#include "nl_ui.h"

#include <private/gl/nl_gl.h>

// Goal of this project is to consolodate the UI projects into 1 project
// The UI should be batched; have its own GL texture sheet for all icons and fonts
// Maybe it has it's own camera too

//This is probably where one of the scenarios becomes the new 4th project instead of consolodating the other 3

// Just read about Uniform Buffer Objects to store the same values in multiple shaders
// Probably not relevant to the current thing where I want to use 2 different cameras as different rendering areas
// but maybe in the future

global_variable ui_element center_square = {0};
global_variable ui_element square_ur = {0};
global_variable ui_element square_bl = {0};
global_variable ui_element mouse_pointer = {0};

void winsizecbk(int width, int height)
{
    ui_set_window_size(width, height);
}

void app_specific_init(void)
{
    ui_init();

    set_window_size_callback(&winsizecbk);
    
    v2i screen_size = get_screen_size();
    winsizecbk(screen_size.x, screen_size.y);
}

void app_specific_update(double dt)
{
    NL_UNUSED(dt);
}

 

void app_specific_render()
{
    ui_render();
    
}

void app_specific_cleanup(void)
{
    ui_cleanup();

    //free_mesh(&center_square.m);
    //free_mesh(&square_ur.m);
    //free_mesh(&square_bl.m);
    //free_mesh(&mouse_pointer.m);
}

#include "nl_ui.c"
#include "nl_mesh_gl.c"
