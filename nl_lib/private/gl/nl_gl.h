#ifndef __NL_GL_H__
#define __NL_GL_H__

#if defined (_WIN32)
#include "nl_gl_win32.h"
#elif defined (__EMSCRIPTEN__)
#include "nl_gl_web.h"
#elif defined (__linux__)
#include "nl_gl_linux.h"
#else
#warning Incomplete opengl platform
#endif

#ifdef __cplusplus
extern "C" {
#endif


int initialize_gl();


#ifdef __cplusplus
}
#endif
#endif //__NL_GL_H__