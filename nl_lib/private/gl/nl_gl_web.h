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

// GL ES doesn't have clamp to border but I was using it.  Maybe shouldn't so I can keep feature parity but I already do this sorta thing above
#ifndef GL_CLAMP_TO_BORDER 
#define GL_CLAMP_TO_BORDER GL_CLAMP_TO_EDGE
#endif

#endif //__NL_GL_WEB_H__