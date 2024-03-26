#include "private/nl_gl.h"

unsigned int fbo = 0;
unsigned int fbo_texture = 0;
unsigned int rbo = 0;

void setup_fbo()
{
    glGenFramebuffers(1, &fbo);
    glGenTexture(1, &fbo_texture);
}

void bind_fbo()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void clean_fbo()
{
    glDeleteFramebuffers(1, &fbo);  
}
