#ifndef __NL_MEMORY_H__
#define __NL_MEMORY_H__


#ifdef __cplusplus
extern "C" {
#endif

#if 0 && !defined(__PSX__) // to find memory leaks
#include <stddef.h>
#define memory_allocate(s) _memory_allocate(s); NL_LOG("%s %d", __FILE__, __LINE__);
#else 
#define memory_allocate(s) _memory_allocate(s);
#endif

void *_memory_allocate(size_t size);
void memory_free(void* memory);

void basic_memory_leak_check(); //Used in debug + by main


#ifdef __cplusplus
}
#endif
#endif //__NL_MEMORY_H__