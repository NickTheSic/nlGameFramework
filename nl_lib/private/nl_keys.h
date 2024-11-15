#ifndef __NL_KEYS_H__
#define __NL_KEYS_H__

typedef enum nl_key nl_key;

#if defined(_WIN32)
#include "win32/nl_keys_win32.h"

#elif defined(__EMSCRIPTEN__)
#include "web/nl_keys_web.h"

#elif defined(__linux__)
#include "linux/nl_keys_linux.h"

#elif defined(GEKKO)
#include "gcn/nl_keys_gcn.h"

#else
#error incomplete platform
#endif

#endif