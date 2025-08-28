#ifndef __NL_DEBUG_H__
#define __NL_DEBUG_H__

#include <stdio.h>
#define NL_LOG(m,...) fprintf(stdout, m,##__VA_ARGS__); fprintf(stdout, "\n");

#define DO_ONCE(thing) {static int doonce = 1; if (doonce){ doonce = 0; thing; }}

#ifdef NL_STRIP_DEBUG
#   define NL_UNIMPLEMENTED_FUNC
#   define NL_DEPRECATED_FUNC
#   define NL_UNUSED(x) (void)(x);
#else
#   define NL_UNIMPLEMENTED_FUNC DO_ONCE(NL_LOG("Unimplemented Function %s in %s", __FUNCTION__, __FILE__););
#   define NL_DEPRECATED_FUNC(replace) DO_ONCE(NL_LOG("Deprecated Function %s in %s, replace with %s", __FUNCTION__, __FILE__, replace););
#   define NL_UNUSED(x) (void)(x); //DO_ONCE(NL_LOG("variable %s is not being used in %s", #x, __FUNCTION__););
#endif

#define internal_function static inline
#define global_variable static
#define local_persist static

#define QUOTE_STR(name) #name // turn the value passed in into a string
#define VALUE_TO_STR(name) QUOTE_STR(name) // Use this as for some reason the above doesn't work on its own

#endif //__NL_DEBUG_H__