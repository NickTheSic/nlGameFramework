
#ifndef __NL_DEBUG_H__
#define __NL_DEBUG_H__

#ifdef __cplusplus
extern "C" {
#endif


// TODO: Coloured loggin, cus why not


#define NL_DEBUG_ENABLED 1  // Temporary Solution: It is hard coded on or off here instead of a Config.h per project or a compiler flag


//  So I can use the non _s versions of functions for windows
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define NL_LOG(m,...) fprintf(stdout, m,##__VA_ARGS__); fprintf(stdout, "\n");

#define DO_ONCE(thing) {static int local_do_once = 1; if (local_do_once){ local_do_once = 0; thing; }}

#define internal_function static inline
#define global_variable static
#define local_persist static

#define QUOTE_STR(name) #name // turn the value passed in into a string
#define VALUE_TO_STR(name) QUOTE_STR(name) // Use this as for some reason the above doesn't work on its own

#define DEBUG_RANDOM_BACKGROUND_COLOUR set_background_colour_4f(random_float_in_range(0.0f,1.0f),random_float_in_range(0.0f,1.0f),random_float_in_range(0.0f,1.0f),1.0f);

#if NL_DEBUG_ENABLED

# ifdef _WIN32
#  define NL_DEBUG_BREAK() __debugbreak()
# else
#  define NL_DEBUG_BREAK()
# endif

# define NL_UNIMPLEMENTED_FUNC DO_ONCE(NL_LOG("Unimplemented Function %s in %s", __FUNCTION__, __FILE__););
# define NL_DEPRECATED_FUNC(replace) DO_ONCE(NL_LOG("Deprecated Function %s in %s, replace with %s", __FUNCTION__, __FILE__, replace););
# define NL_UNUSED(x) (void)(x); DO_ONCE(NL_LOG("variable %s is not being used in %s", #x, __FUNCTION__););
# define NL_ASSERT(x, m,...) {if(!(x)){NL_LOG(m,##__VA_ARGS__); NL_DEBUG_BREAK();}}
#else
# define NL_UNIMPLEMENTED_FUNC
# define NL_DEPRECATED_FUNC(replace)
# define NL_UNUSED(x) (void)(x);
# define NL_ASSERT(x)
#endif


#ifdef __cplusplus
}
#endif

#endif //__NL_DEBUG_H__