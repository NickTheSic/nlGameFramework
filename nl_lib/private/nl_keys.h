#ifndef __NL_KEYS_H__
#define __NL_KEYS_H__

typedef enum nl_key nl_key;

#ifdef _WIN32
#include "win32/nl_keys_win32.h"
#endif

#ifdef __EMSCRIPTEN__
#include "web/nl_keys_web.h"
#endif

#endif