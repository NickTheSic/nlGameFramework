#include "nl_framebuffer.h"
#include "private/nl_gl.h"

void init_framebuffer(FBO* fbo, unsigned int fx, unsigned int fy)
{
    glGenFramebuffers(1, &fbo->framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo->framebuffer);

    glGenTextures(1, fbo->texture);
    glBindTexture(fbo->texture);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, fx, fy, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, fbo->texture, 0);

    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);
}

void free_framebuffer(FBO* fbo)
{
    glDeleteTextures(1, fbo->texture);
    glDeleteBuffers(1, fbo->framebuffer);
}
