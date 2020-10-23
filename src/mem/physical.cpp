#include <mem/physical.h>
#include <std/cstdio.h>
#include <lib/bit.h>

namespace phys
{

    uint32_t *memoryBitmap;
    uint32_t initialBitmap[] = {0xffffff7f};
    uint32_t *tempBitmap;

    size_t bitmapEntries = 32;

    size_t totalPages = 1;
    size_t freePages = 1;

    __attribute__((always_inline)) static inline int readBitmap(size_t i)
    {
        i -= BITMAP_BASE;

        return testBit(memoryBitmap, i);
    }

    __attribute__((always_inline)) static inline void setBitmap(size_t i, size_t count)
    {
        i -= BITMAP_BASE;

        freePages -= count;

        size_t f = i + count;
        for (size_t j = i; j < f; j++)
            setBit(memoryBitmap, j);
    }

    __attribute__((always_inline)) static inline void unsetBitmap(size_t i, size_t count)
    {
        i -= BITMAP_BASE;

        freePages += count;

        size_t f = i + count;
        for (size_t j = i; j < f; j++)
            resetBit(memoryBitmap, j);
    }

    void *alloc(size_t pageCount)
    {

        size_t initialPageCount = pageCount;

        size_t i;
        for (i = BITMAP_BASE; i < BITMAP_BASE + bitmapEntries;)
        {
            if (!readBitmap(i++))
            {
                if (!--initialPageCount)
                {
                    size_t start = i - pageCount;
                    setBitmap(start, pageCount);

                    // Return the physical address that represents the start of this physical page(s).
                    return (void *)(start * PAGE_SIZE);
                }
            }
            else
            {
                initialPageCount = pageCount;
            }
        }
        std::printf("alloc returning 0\n");
        return 0;
    }

    /* Allocate physical memory and zero it out. */
    void *allocz(size_t pageCount)
    {
        void *ptr = alloc(pageCount);
        if (!ptr)
            return NULL;
        uint64_t *pages = (uint64_t *)((size_t)ptr + MEM_PHYS_OFFSET);

        for (size_t i = 0; i < (pageCount * PAGE_SIZE) / sizeof(uint64_t); i++)
        {
            pages[i] = 0;
        }

        return ptr;
    }

    void free(void *ptr, size_t pageCount)
    {
        size_t start = (size_t)ptr / PAGE_SIZE;
        unsetBitmap(start, pageCount);
    }

    void init(stivale_memmap *memmap)
    {
        memoryBitmap = initialBitmap;
        if (!(tempBitmap = (uint32_t *)allocz(BMREALLOC_STEP)))
        {
            std::printf("allocz error\n");
            return;
        }

        tempBitmap = (uint32_t *)((size_t)tempBitmap + MEM_PHYS_OFFSET);

        for (size_t i = 0; i < (BMREALLOC_STEP * PAGE_SIZE) / sizeof(uint32_t); i++)
            tempBitmap[i] = 0xffffffff;

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

                if (addr < (MEMORY_BASE + PAGE_SIZE /* bitmap */))
                    continue;

                if (addr >= (MEMORY_BASE + bitmapEntries * PAGE_SIZE))
                {
                    /* Reallocate bitmap */
                    size_t currentBitmapSize = ((bitmapEntries / 32) * sizeof(uint32_t)) / PAGE_SIZE;
                    size_t newBitmapSize = currentBitmapSize + BMREALLOC_STEP;
                    if (!(tempBitmap = (uint32_t *)allocz(newBitmapSize)))
                    {
                        return;
                    }
                    tempBitmap = (uint32_t *)((size_t)tempBitmap + MEM_PHYS_OFFSET);
                    /* Copy over previous bitmap */
                    for (size_t i = 0;
                         i < (currentBitmapSize * PAGE_SIZE) / sizeof(uint32_t);
                         i++)
                        tempBitmap[i] = memoryBitmap[i];
                    /* Fill in the rest */
                    for (size_t i = (currentBitmapSize * PAGE_SIZE) / sizeof(uint32_t);
                         i < (newBitmapSize * PAGE_SIZE) / sizeof(uint32_t);
                         i++)
                        tempBitmap[i] = 0xffffffff;
                    bitmapEntries += ((PAGE_SIZE / sizeof(uint32_t)) * 32) * BMREALLOC_STEP;
                    uint32_t *oldBitmap = (uint32_t *)((size_t)memoryBitmap - MEM_PHYS_OFFSET);
                    memoryBitmap = tempBitmap;
                    free(oldBitmap, currentBitmapSize);
                }

                if (entry->type == USABLE)
                {
                    totalPages++;
                    unsetBitmap(page, 1);
                }
            }
        }
        std::printf(" %Cg✓%C0  Physical Memory.\n");
    }

} // namespace phys