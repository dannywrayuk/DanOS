#pragma once
#include <stdint.h>
#include <boot/stivale.h>
#include <stddef.h>

#define PAGE_SIZE ((size_t)0x1000)
#define MEMORY_BASE 0x1000000
#define BITMAP_BASE (MEMORY_BASE / PAGE_SIZE)
#define MEM_PHYS_OFFSET ((size_t)0xffff800000000000)

namespace phys
{

    void init(stivale_memmap *memmap);

    void *calloc(size_t pageCount);

    void *malloc(size_t pageCount);

    void *realloc(void *ptr, size_t pageCount, size_t newPageCount);

    void *recalloc(void *ptr, size_t pageCount, size_t newPageCount);

    void free(void *ptr, size_t pageCount);

} // namespace phys
