#ifndef __NL_MEMORY_H__
#define __NL_MEMORY_H__

void *memory_allocate(unsigned long long size);
void memory_free(void* memory);

#endif //__NL_MEMORY_H__