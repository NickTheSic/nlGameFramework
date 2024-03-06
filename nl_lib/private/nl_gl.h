#ifndef __NL_GL_H__
#define __NL_GL_H__

#ifdef _WIN32
#include "win32/nl_gl_win32.h"
#endif

#ifdef __EMSCRIPTEN__
#include "web/nl_gl_web.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif


int initialize_gl();


#ifdef __cplusplus
}
#endif
#endif //__NL_GL_H__