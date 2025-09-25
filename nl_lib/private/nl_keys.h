#ifndef __NL_KEYS_H__
#define __NL_KEYS_H__

#if defined(_WIN32)
#include "win32/nl_keys_win32.h"

#elif defined(__EMSCRIPTEN__)
#include "web/nl_keys_web.h"

//#elif defined(__linux__)
//#include "linux/nl_keys_linux.h"

#else
#include "null/nl_keys_null.h"
#endif

// The includes include the actual enum definition
// this is here after the fact so I can use nl_key 
typedef enum nl_key nl_key;

#endif