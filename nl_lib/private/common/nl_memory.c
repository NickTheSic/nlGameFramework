#include <private/nl_memory.h>
#include <private/nl_debug.h>

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>


global_variable size_t _ESTIMATED_USED_MEMORY = {0};


#if NL_DEBUG_ENABLED
internal_function void* internal_allocate_memory(size_t size)
{
    NL_LOG("Debug Memory Allocated");
    size_t* memory = (size_t*)malloc(sizeof(size_t)+size);
    if (memory == 0)
    {
        NL_LOG("Unable to allocate memory of size %zi", size);
        return 0;
    }

    _ESTIMATED_USED_MEMORY+=size;
    *memory = size;

    return (void*)((size_t)memory+sizeof(size_t));
}

internal_function void internal_free_memory(void* ptr)
{
    size_t* real_ptr = (size_t*)(ptr-sizeof(size_t));

    size_t size = real_ptr[0];
    _ESTIMATED_USED_MEMORY-=size;

    free(real_ptr);
}
#else
internal_function void* internal_allocate_memory(size_t size)
{
    void* memory = (void*)malloc(size);

    if (memory == 0)
    {
        NL_LOG("Unable to allocate memory of size %zi", size);
        return 0;
    }

    return memory;
}
#define internal_free_memory(ptr) free(ptr);
#endif

void *_memory_allocate(size_t size)
{
    void* memory = (void*)internal_allocate_memory(size);

    memset(memory, 0, size);
    return memory;
}

// maybe a void** to be able to set it to 0 here too?
void memory_free(void* memory)
{
    internal_free_memory(memory);
}

void basic_memory_leak_check(void)
{
    if (_ESTIMATED_USED_MEMORY == 0)
    {
        NL_LOG("No Memory Leak Detected");
    }
    else
    {
        NL_LOG("Memory Leak! Leaked Memory Amount: %zi", _ESTIMATED_USED_MEMORY);
    }
}
