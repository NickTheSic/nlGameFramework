#include "../nl_memory.h"

#include <stdlib.h>
#include <memory.h>

local_variable int _BASIC_MEMORY_COUNTER = {0}

void *memory_allocate(size_t size)
{
    void* memory = (void*)malloc(size);
    if (memory == 0)
    {
        // Some sort of error handling
        return 0;
    }

    ++_BASIC_MEMORY_COUNTER;

    memset(memory, 0, size);
    return memory;
}

// maybe a void** to be able to set it to 0 here too?
void memory_free(void* memory)
{
    free(memory);

    --_BASIC_MEMORY_COUNTER;
}

void basic_memory_leak_check()
{
    if (_BASIC_MEMORY_COUNTER > 0)
    {
        NL_LOG("More memory allocations than frees: %d", _BASIC_MEMORY_COUNTER);
    }
    else if (_BASIC_MEMORY_COUNTER < 0)
    {
        NL_LOG("More memory frees than allocations: %d", _BASIC_MEMORY_COUNTER);
    }
    else
    {
        NL_LOG("No leaks detected");
    }
}
