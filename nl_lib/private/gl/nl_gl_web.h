#ifndef __NL_GL_WEB_H__
#define __NL_GL_WEB_H__
 
#include <emscripten.h>
#include <emscripten/html5_webgl.h>
#include "nl_egl.h"

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

#endif //__NL_GL_WEB_H__