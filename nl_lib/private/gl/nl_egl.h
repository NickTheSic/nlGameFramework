#ifndef __NL_GLES_H__
#define __NL_GLES_H__

#include <EGL/egl.h>

typedef struct EGLRenderer EGLRenderer;
struct EGLRenderer
{
   EGLDisplay display;
   EGLSurface surface;
   EGLContext context;
};
extern EGLRenderer g_EGLRenderer;

int initialize_egl(NativeWindowType platform_window);

#endif//__NL_GLES_H__