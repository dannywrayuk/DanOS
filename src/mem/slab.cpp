#include <lib/bitmap.h>
#include <mem/cmem.h>
#include <mem/physical.h>
#include <mem/slab.h>

#include <std/cstdio.h>

namespace slab
{
    bitmap_t *bitmap;
    size_t *base;

    void init()
    {
        bitmap = bitmap::create();
        base = (size_t *)phys::calloc(1);

        std::printf(" %Cg✓%C0  Slab Allocator.\n");
    }

    void *malloc(size_t size)
    {
        if (!size)
            return (void *)0;

        size_t gapSize = 0;

        if ((size + 1) % 2)
        {
            size++;
        }

        for (size_t i = 0;; i++)
        {
            if (!bitmap::get(bitmap, i))
            {
                gapSize++;
                if (gapSize > size)
                {
                    bitmap::set(bitmap, i - size, 1, gapSize);
                    uint8_t *address = (uint8_t *)base + i - size + 1;
                    *(address - 1) = (uint8_t)gapSize;
                    return (void *)address;
                }
            }
            else
            {
                gapSize = 0;
            }
        }
    }

    void *malloc()
    {
        return malloc(1);
    }

    void *calloc()
    {
        return calloc(1);
    }

    void *calloc(size_t size)
    {
        void *ptr = malloc(size);
        memset(ptr, 0, *((uint8_t *)ptr - 1) - 1);
        return ptr;
    }

    void free(void *ptr)
    {
        size_t size = *((uint8_t *)ptr - 1);
        uint32_t adress = (uint32_t)((uint64_t)ptr - (uint64_t)base - 1);
        bitmap::set(bitmap, adress, 0, size);
    }

} // namespace slab