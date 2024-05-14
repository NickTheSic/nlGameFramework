#include "nl_lib.h"
#include "private/nl_gl.h"

global_variable unsigned int FBO = 0;
global_variable unsigned int texture = 0;
global_variable unsigned int rbo = 0;

void app_specific_init(void)
{
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);


    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE, texture);
    // 800,600 is screen size.  if I want to resize this may not work
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,   800, 600,   0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  


    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);


    glGenRenderbuffers(1, &rbo);
    glBindRenderBuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600); 

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);  

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        NL_LOG("Framebuffer status incomplete");
    }

}

void app_specific_update(double dt)
{
    
}

void app_specific_cleanup(void)
{
    glDeleteFrameBuffers(1, &FBO);
}
