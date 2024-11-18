#ifndef __NL_FRAMEBUFFER_H__
#define __NL_FRAMEBUFFER_H__

typedef struct FBO FBO;
struct FBO
{
    unsigned int framebuffer;
    unsigned int texture;
};

void init_framebuffer(FBO* fbo);
void free_framebuffer(FBO* fbo);

#endif//__NL_FRAMEBUFFER_H__