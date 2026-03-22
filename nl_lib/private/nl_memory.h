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


// Note: Look into arena allocator as well probably the same name!
// Can RESERVE a large chunk of memory and COMMIT when needed, the DECOMMIT when unused
// Someone called it a scratch arena and using 2 scratch areana per thread to handle arbitrary function depth and

typedef struct nl_bump_allocator nl_bump_allocator;
struct nl_bump_allocator
{
    char* memory;
    size_t capacity;
    size_t used;
};

void make_bump_allocator(nl_bump_allocator* allocator, size_t capacity);
void flush_bump_allocator(nl_bump_allocator* allocator);
void free_bump_allocator(nl_bump_allocator* allocator);
char* bump_alloc(nl_bump_allocator* allocator, size_t size);


// I don't like this but it works well enough I think
void initialize_global_bump_allocators(size_t transient, size_t temporary);
void free_global_bump_allocators();
nl_bump_allocator* get_transient_bump_allocator(); 
nl_bump_allocator* get_temporary_bump_allocator(); // Buffer for loaded files pretty much
// NOTE: Could make Systems bump allocator for different things
//       - some one mentioned Scratch, and I called it temporary
//       - Handle the per 'scene' lifetime, per game life time


void *_memory_allocate(size_t size);
void memory_free(void* memory);

#if NL_DEBUG_ENABLED

void _basic_memory_leak_check(void); //Used in debug + by main
# define memory_allocate(s) _memory_allocate(s); NL_LOG("memory allocated: %s %d", __FILE__, __LINE__);
# define basic_memory_leak_check() _basic_memory_leak_check();

#else //NOT NL_DEBUG_ENABLED

# define memory_allocate(s) _memory_allocate(s);
# define basic_memory_leak_check()

#endif//NL_DEBUG_ENABLED


#ifdef __cplusplus
}
#endif

#endif //__NL_MEMORY_H__