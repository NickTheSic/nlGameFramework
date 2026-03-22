#include <private/nl_memory.h>
#include <private/nl_debug.h>

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>


#if NL_DEBUG_ENABLED

global_variable size_t _ESTIMATED_USED_MEMORY = {0};
global_variable size_t _MallocCalls = {0};
global_variable size_t _FreeCalls = {0};

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

    NL_LOG("Memory[0]: %zu", memory[0]);

    ++_MallocCalls;

    return (void*)((size_t*)memory+sizeof(size_t));
}

internal_function void internal_free_memory(void* ptr)
{
    size_t* real_ptr = (size_t*)((size_t*)ptr-sizeof(size_t));

    size_t size = real_ptr[0];
    NL_LOG("Freeing size %zu", size);

    _ESTIMATED_USED_MEMORY-=size;
    ++_FreeCalls;

    free(real_ptr);
}

void _basic_memory_leak_check(void)
{
    if (_ESTIMATED_USED_MEMORY == 0)
    {
        NL_LOG("No Memory Leak Detected in %zu allocs and %zu frees", _MallocCalls, _FreeCalls);
    }
    else
    {
        NL_LOG("Memory Leak! Leaked Memory Amount: %zu bytes", _ESTIMATED_USED_MEMORY);
        NL_LOG("Used %zu malloc calls and %zu frees", _MallocCalls, _FreeCalls);
    }
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

# define internal_free_memory(ptr) free(ptr);

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



void make_bump_allocator(nl_bump_allocator* allocator, size_t capacity)
{
    NL_ASSERT(0==allocator->memory,"Bump memory already allocated");

    allocator->memory = (char*)memory_allocate(capacity); // calls malloc and sets to 0

    if (!allocator->memory)
    {
        NL_LOG("Bump Allocator: Failed to allocate memory.");
        return;
    }

    allocator->capacity = capacity;
}

void flush_bump_allocator(nl_bump_allocator* allocator)
{
    allocator->used = 0;
    memset(allocator->memory, 0, allocator->capacity);
}

void free_bump_allocator(nl_bump_allocator* allocator)
{
    NL_LOG("Freeing bump Allocator");
    allocator->used = 0;
    
    memory_free(allocator->memory);
    
    allocator->capacity = 0;
    allocator->memory = 0;
}

char* bump_alloc(nl_bump_allocator* allocator, size_t size)
{
    // Basic alignedment to an 16 bit boundary?  I have to figure out if this is good or not
    size_t aligned_size = (size+15) & ~15;

    if (allocator->used + aligned_size > allocator->capacity)
    {
        NL_LOG("Bump Allocator: Unable to allocate we are full");
        return 0;
    }

    char* chunk = allocator->memory + allocator->used;

    allocator->used += aligned_size;

    return chunk;
}


nl_bump_allocator global_transient_bump_allocator;
nl_bump_allocator global_temporary_bump_allocator;

void initialize_global_bump_allocators(size_t transient, size_t temporary)
{
    NL_LOG("Allocating global bump allocators! %zu transient bufffer and %zu temporary", transient, temporary);

    make_bump_allocator(&global_transient_bump_allocator, transient);
    make_bump_allocator(&global_temporary_bump_allocator, temporary);
}

void free_global_bump_allocators()
{
    free_bump_allocator(&global_transient_bump_allocator);
    free_bump_allocator(&global_temporary_bump_allocator);
}

nl_bump_allocator* get_transient_bump_allocator()
{
    return &global_transient_bump_allocator;
}

nl_bump_allocator* get_temporary_bump_allocator()
{
    return &global_temporary_bump_allocator;
}
