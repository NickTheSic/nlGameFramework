#ifndef __NL_SCOPE_TIMER_H__
#define __NL_SCOPE_TIMER_H__

#include "nl_debug.h"

// NOTE: __attribute(__cleanup(func)) is not available with the MSVC compiler (apprently; should test)

#if NL_DEBUG_ENABLED
typedef struct debug_scope_timer debug_scope_timer;
struct debug_scope_timer
{
    const char* name;
    double ms;
};

double debug_get_system_time();
void debug_end_scope_timer(debug_scope_timer* const st);

#if defined(__EMSCRIPTEN__)

#define SCOPE_TIMER(label) \
debug_scope_timer scope_##__LINE__ __attribute__((cleanup(debug_end_scope_timer))) = {label,debug_get_system_time()};

#else

#define SCOPE_TIMER(label) \
debug_scope_timer scope_##__LINE__ __attribute__((cleanup(debug_end_scope_timer))) = {label,debug_get_system_time()};\
scope_##__LINE__.ms = debug_get_system_time();

#endif //EMSCRIPTEN

#else
#define SCOPE_TIMER(label)
#endif


#endif//__NL_SCOPE_TIMER_H__