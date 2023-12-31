#ifndef __NL_MEMORY_H__
#define __NL_MEMORY_H__

#include <stddef.h>

void *memory_allocate(size_t size);
void memory_free(void* memory);

#endif //__NL_MEMORY_H__