#include "../nl_memory.h"

#include <stdlib.h>
#include <memory.h>

void *memory_allocate(size_t size)
{
    void* memory = (void*)malloc(size);
    if (memory == 0)
    {
        // Some sort of error handling
        return 0;
    }

    memset(memory, 0, size);
    return memory;
}

// maybe a void** to be able to set it to 0 here too?
void memory_free(void* memory)
{
    free(memory);
}
