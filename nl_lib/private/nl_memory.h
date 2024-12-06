#ifndef __NL_MEMORY_H__
#define __NL_MEMORY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

void *_memory_allocate(size_t size);
void memory_free(void* memory);

void basic_memory_leak_check(); //Used in debug + by main

#if defined(__PSX__) || 1
#define memory_allocate(s) _memory_allocate(s);
#else 
#define memory_allocate(s) _memory_allocate(s); NL_LOG("memory allocated: %s %d", __FILE__, __LINE__);
#endif


#ifdef __cplusplus
}
#endif
#endif //__NL_MEMORY_H__