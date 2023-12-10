#include "nl_lib.h"
#include "private/nl_gl.h"

global_variable unsigned int FBO = 0;


void app_specific_init(void)
{
    glGenFramebuffers(1, &FBO);

    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void app_specific_update(double dt)
{
    
}
