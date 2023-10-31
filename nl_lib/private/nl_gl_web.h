#ifndef __NL_GL_WEB_H__
#define __NL_GL_WEB_H__
 
#include <emscripten.h>

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

typedef struct EGLRenderer EGLRenderer;
struct EGLRenderer
{
   EGLDisplay display;
   EGLSurface surface;
   EGLContext context;
};
extern EGLRenderer g_EGLRenderer;

#endif //__NL_GL_WEB_H__