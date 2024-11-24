#ifndef __NL_GLES_H__
#define __NL_GLES_H__

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#define GL_GLEXT_PROTOTYPES
#include <GLES2/gl2ext.h>

#ifndef glBindVertexArray
#define glBindVertexArray    glBindVertexArrayOES
#endif
#ifndef glGenVertexArrays
#define glGenVertexArrays    glGenVertexArraysOES
#endif
#ifndef glDeleteVertexArrays
#define glDeleteVertexArrays glDeleteVertexArraysOES
#endif
#ifndef glPolygonMode
#define glPolygonMode        glPolygonModeNV
#endif

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