#include "nl_lib.h"
#include "private/nl_gl.h"

// The idea is I setup a FBO that renders the actual game
// Then I render that into a fake scene that I can resize...
// Should actually define what a game class does.
// Also should setup a) specific functions I need to implement and call.  I guess do that as function ptrs.
// interesting to setup that the core code finds all these functions in a dll, 
// but this dll happens to be the editor which loads the games functions!

void app_specific_init(void)
{

}

void app_specific_update(double dt)
{
    (void)dt;
}
