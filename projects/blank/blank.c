#include "nl_lib.h"

// Intentionally Empty for purpose of testing

void app_specific_init(void){DO_ONCE(NL_LOG("App Init!"););}
void app_specific_update(double dt){NL_UNUSED(dt);DO_ONCE(NL_LOG("App Update!"););}
void app_specific_render(void){DO_ONCE(NL_LOG("App Render!"););}
void app_specific_cleanup(void){DO_ONCE(NL_LOG("App Cleanup!"););}
