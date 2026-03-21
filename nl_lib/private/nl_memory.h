#ifndef __NL_MEMORY_H__
#define __NL_MEMORY_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


// TODO: This was a wrapper around malloc and free so I could make my own memory allocator in the future
// Maybe I want to consider VirtualAlloc on windows and do the Handmade Hero stuff?

// verbose names? Just in case? 
#define KB(x) ((unsigned long long)1024*x)
#define MB(x) ((unsigned long long)1024*KB(x))
#define GB(x) ((unsigned long long)1024*MB(x))


typedef struct nl_bump_allocator nl_bump_allocator;
struct nl_bump_allocator
{
    size_t capacity;
    size_t used;
    char* memory;
};

void make_bump_allocator(nl_bump_allocator* allocator, size_t capacity);
void flush_bump_allocator(nl_bump_allocator* allocator);
void free_bump_allocator(nl_bump_allocator* allocator);
char* bump_alloc(nl_bump_allocator* allocator, size_t size);

// create a global transient allocator located in nl_memory.c
void create_global_transient_bump_allocator(size_t capacity);
void free_global_transient_bump_allocator();
// this will auto flush the global transient bump allocator!  Nothing is safe
void *global_transient_bump_allocate(size_t size);


void *_memory_allocate(size_t size);
void memory_free(void* memory);

#if NL_DEBUG_ENABLED

void _basic_memory_leak_check(void); //Used in debug + by main
# define memory_allocate(s) _memory_allocate(s); NL_LOG("memory allocated: %s %d", __FILE__, __LINE__);
# define basic_memory_leak_check() _basic_memory_leak_check();

#else

# define memory_allocate(s) _memory_allocate(s);
# define basic_memory_leak_check()

#endif


#ifdef __cplusplus
}
#endif

#endif //__NL_MEMORY_H__