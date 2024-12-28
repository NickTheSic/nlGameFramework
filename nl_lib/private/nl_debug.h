#ifndef __NL_DEBUG_H__
#define __NL_DEBUG_H__

// Could hide these in a platform specific debug header
#if defined(PSP)
#   include <pspdebug.h> 
#   if defined(PSP_DEBUG_RENDERER)
#       define NL_LOG(m,...) pspDebugScreenPrintf(m,##__VA_ARGS__);
#   else
#       define NL_LOG(m,...)
#   endif
#if defined(_WIN32)
#   include <stdio.h>
#   define NL_LOG(m,...) fprintf(stdout, m,##__VA_ARGS__); fprintf(stdout, "\n");
#   endif
#else
#   include <stdio.h>
#   define NL_LOG(m,...) fprintf(stdout, m,##__VA_ARGS__); fprintf(stdout, "\n");
#endif

#define DO_ONCE(thing) {static int doonce = 1; if (doonce){ doonce = 0; thing; }}
#define NL_UNIMPLEMENTED_FUNC DO_ONCE(NL_LOG("Unimplemented Function %s in %s", __FUNCTION__, __FILE__););
#define NL_DEPRECATED_FUNC(replace) DO_ONCE(NL_LOG("Deprecated Function %s in %s, replace with %s", __FUNCTION__, __FILE__, replace););

#define internal_function static inline
#define global_variable static
#define local_persist static

#define NL_UNUSED(x) (void)(x); DO_ONCE(NL_LOG("variable %s is not being used in %s", #x, __FUNCTION__););

#define QUOTE_STR(name) #name // turn the value passed in into a string
#define VALUE_TO_STR(name) QUOTE_STR(name) // Use this as for some reason the above doesn't work on its own

#endif //__NL_DEBUG_H__