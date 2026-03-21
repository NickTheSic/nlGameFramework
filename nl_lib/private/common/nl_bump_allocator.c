#include "private/nl_bump_allocator.h"
#include "private/nl_memory.h"

/*
struct nl_bump_allocator
{
    size_t capacity;
    size_t used;
    char* memory;
};

*/

void make_bump_allocator(nl_bump_allocator* allocator, size_t capacity)
{
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
    free_memory(allocator->memory);
    allocator->memory = allocator->used = allocator->capacity = 0;
}

char* bump_alloc(nl_bump_allocator* allocator, size_t size)
{
    if (allocator->used + size > allocator->capacity)
    {
        NL_LOG("Bump Allocator: Unable to allocate we are full");
        return 0;
    }

    char* chunk = allocator->memory + allocator->used;

    allocator->used += size;

    return chunk;
}
