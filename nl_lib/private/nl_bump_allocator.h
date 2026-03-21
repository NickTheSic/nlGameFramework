#ifndef __NL_BUMP_ALLOCATOR_H__
#define __NL_BUMP_ALLOCATOR_H__

typedef struct nl_bump_allocator nl_bump_allocator;
struct nl_bump_allocator
{
    size_t capacity;
    size_t used;
    char* memory;
};

void make_bump_allocator(nl_bump_allocator* allocator, size_t capacity);
void flush_bump_allocator(nl_bump_allocator* allocator);
void free_bump_allocator(nl_bump_allocator* allocator);

char* bump_alloc(nl_bump_allocator* allocator, size_t size);

#endif//__NL_BUMP_ALLOCATOR_H__