#include "../nl_memory.h"

#include <stdlib.h>

void *memory_allocate(size_t size)
{
    void* memory = (void*)malloc(size);
    return memory;
}

void memory_free(void* memory)
{
    free(memory);
}
