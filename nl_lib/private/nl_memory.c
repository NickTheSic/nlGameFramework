#include "../nl_memory.h"

#include <stdlib.h>

void *memory_allocate(size_t size)
{
    return (void*)malloc(size);
}

void memory_free(void* memory)
{
    free(memory);
}
