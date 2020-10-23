#pragma once
#include <stdint.h>
#include <boot/stivale.h>
#include <stddef.h>

#define PAGE_SIZE ((size_t)0x1000)
#define MEMORY_BASE 0x1000000
#define BITMAP_BASE (MEMORY_BASE / PAGE_SIZE)
#define MEM_PHYS_OFFSET ((size_t)0xffff800000000000)

#define BMREALLOC_STEP 1

namespace phys
{
    void init(stivale_memmap *memmap);

    void *allocz(size_t pageCount);

    void *alloc(size_t pageCount);

    void free(void *ptr, size_t pageCount);

} // namespace phys
