#include <mem/physical.h>
#include <std/cstdio.h>
#include <mem/cmem.h>
#include <lib/bitmap.h>

namespace phys
{

    bitmap_t *bitmap;

    void *malloc(size_t pageCount)
    {
        size_t initialPageCount = bitmap->pages;
        for (size_t i = 0; i < bitmap->pages * bitmap::bitsPerPage;)
        {
            if (!bitmap::get(bitmap, i++))
            {
                if (!--initialPageCount)
                {
                    size_t start = i - pageCount;
                    bitmap::set(bitmap, start, 1, pageCount);
                    return (void *)(start * PAGE_SIZE);
                }
            }
            else
            {
                initialPageCount = pageCount;
            }
        }
        std::printf("malloc returning 0\n");
        return 0;
    }

    void free(void *ptr, size_t pageCount)
    {
        size_t start = (size_t)ptr / PAGE_SIZE;
        bitmap::set(bitmap, start, 0, pageCount);
    }

    void *calloc(size_t pageCount)
    {
        void *ptr = malloc(pageCount);
        if (!ptr)
            return NULL;

        uint64_t *pages = (uint64_t *)((size_t)ptr + MEM_PHYS_OFFSET);

        for (size_t i = 0; i < (pageCount * PAGE_SIZE) / sizeof(uint64_t); i++)
        {
            pages[i] = 0;
        }
        return ptr;
    }

    void *realloc(void *ptr, size_t pageCount, size_t newPageCount)
    {
        if (!ptr)
            return malloc(newPageCount);
        if (!newPageCount)
        {
            free(ptr, pageCount);
            return (void *)0;
        }

        if (pageCount == newPageCount)
            return ptr;

        void *newPtr = malloc(newPageCount);
        if (newPtr == 0)
            return (void *)0;

        if (pageCount > newPageCount)
            memcpy(newPtr, (void *)ptr, newPageCount * PAGE_SIZE);
        else
            memcpy(newPtr, (void *)ptr, pageCount * PAGE_SIZE);

        free(ptr, pageCount);

        return newPtr;
    }

    void *recalloc(void *ptr, size_t pageCount, size_t newPageCount)
    {
        if (!ptr)
            return calloc(newPageCount);
        if (!newPageCount)
        {
            free(ptr, pageCount);
            return (void *)0;
        }

        if (pageCount == newPageCount)
            return ptr;

        void *newPtr = calloc(newPageCount);
        if (newPtr == 0)
            return (void *)0;

        if (pageCount > newPageCount)
            memcpy(newPtr, (void *)ptr, newPageCount * PAGE_SIZE);
        else
            memcpy(newPtr, (void *)ptr, pageCount * PAGE_SIZE);

        free(ptr, pageCount);

        return newPtr;
    }

    void init(stivale_memmap *memmap)
    {
        bitmap = bitmap::create((void *)MEMORY_BASE, 1);
        bitmap::setInt(bitmap, 0, 0xffffff7f);

        if ((size_t)bitmap->location <= MEM_PHYS_OFFSET)
            bitmap->location = (uint32_t *)((size_t)bitmap->location + MEM_PHYS_OFFSET);

        for (size_t i = 1; i < bitmap->pages * bitmap::intsPerPage; i++)
            bitmap::setInt(bitmap, i, 0xFFFFFFFF);

        for (size_t i = 0; i < memmap->entries; i++)
        {
            size_t alignedBase;
            struct stivale_memmap_entry *entry = &(memmap->address[i]);

            if (entry->base % PAGE_SIZE)
                alignedBase = entry->base + (PAGE_SIZE - (entry->base % PAGE_SIZE));
            else
                alignedBase = entry->base;

            size_t alignedLength = (entry->size / PAGE_SIZE) * PAGE_SIZE;

            if ((entry->base % PAGE_SIZE) && alignedLength)
                alignedLength -= PAGE_SIZE;

            for (size_t j = 0; j * PAGE_SIZE < alignedLength; j++)
            {
                size_t addr = alignedBase + j * PAGE_SIZE;

                size_t page = addr / PAGE_SIZE;

                if (addr < (MEMORY_BASE + PAGE_SIZE))
                    continue;

                if (addr >= (MEMORY_BASE + bitmap->pages * bitmap::bitsPerPage * PAGE_SIZE))
                {
                    bitmap::resize(bitmap, bitmap->pages + 1);
                    if ((size_t)bitmap->location <= MEM_PHYS_OFFSET)
                        bitmap->location = (uint32_t *)((size_t)bitmap->location + MEM_PHYS_OFFSET);

                    for (size_t i = bitmap::intsPerPage * (bitmap->pages - 1); i < bitmap::intsPerPage * bitmap->pages; i++)
                        bitmap::setInt(bitmap, i, 0xFFFFFFFF);
                }

                if (entry->type == USABLE)
                {
                    bitmap::set(bitmap, page, 0);
                }
            }
        }
        std::printf(" %Cg✓%C0  Physical Memory.\n");
    }

} // namespace phys
