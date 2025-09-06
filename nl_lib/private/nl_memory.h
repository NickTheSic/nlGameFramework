#ifndef __NL_MEMORY_H__
#define __NL_MEMORY_H__

#ifdef __cplusplus
extern "C" {
#endif

// TODO: This was a wrapper around malloc and free so I could make my own memory allocator
// Maybe I want to consider VirtualAlloc on windows and do the Handmade Hero stuff?

#include <stddef.h>

void *_memory_allocate(size_t size);
void memory_free(void* memory);

void basic_memory_leak_check(void); //Used in debug + by main

#define memory_allocate(s) _memory_allocate(s); NL_LOG("memory allocated: %s %d", __FILE__, __LINE__);

#ifdef __cplusplus
}
#endif

#endif //__NL_MEMORY_H__