#ifndef __NL_GL_H__
#define __NL_GL_H__

#ifdef _WIN32
#include "private/nl_gl_win32.h"
#endif

#ifdef __EMSCRIPTEN__
#include "private/nl_gl_web.h"
#endif

int initialize_gl();

#endif //__NL_GL_H__