#include <lib/bitmap.h>
#include <mem/physical.h>

#define setBit(base, offset) ({  \
    int ret;                     \
    asm volatile(                \
        "bts [%1], %2;"          \
        : "=@ccc"(ret)           \
        : "r"(base), "r"(offset) \
        : "memory");             \
    ret;                         \
})

#define testBit(base, offset) ({ \
    int ret;                     \
    asm volatile(                \
        "bt [%1], %2;"           \
        : "=@ccc"(ret)           \
        : "r"(base), "r"(offset) \
        : "memory");             \
    ret;                         \
})

#define resetBit(base, offset) ({ \
    int ret;                      \
    asm volatile(                 \
        "btr [%1], %2;"           \
        : "=@ccc"(ret)            \
        : "r"(base), "r"(offset)  \
        : "memory");              \
    ret;                          \
})

namespace bitmap
{

    bitmap_t *create()
    {
        return create(1);
    };

    bitmap_t *create(uint32_t initialPages)
    {
        bitmap_t *bitmap;
        bitmap->location = (uint32_t *)phys::calloc(initialPages);
        bitmap->pages = initialPages;
        return bitmap;
    };

    bitmap_t *create(void *base, uint32_t initialPages)
    {
        bitmap_t *bitmap;
        bitmap->location = (uint32_t *)base;
        bitmap->pages = initialPages;
        return bitmap;
    };

    void destroy(bitmap_t *bitmap)
    {
        phys::free(bitmap->location, bitmap->pages);
    }

    void resize(bitmap_t *bitmap, uint32_t requiredPages)
    {
        bitmap->location = (uint32_t *)phys::recalloc(bitmap->location, bitmap->pages, requiredPages);
        bitmap->pages = requiredPages;
    }

    void set(bitmap_t *bitmap, uint32_t address, uint32_t value)
    {
        if (address >= bitmap->pages * bitsPerPage)
        {
            uint32_t requiredPages = 1 + address / bitsPerPage;
            resize(bitmap, requiredPages);
        }

        if (value)
        {
            setBit(bitmap->location, address);
        }
        else
        {
            resetBit(bitmap->location, address);
        }
    }

    void set(bitmap_t *bitmap, uint32_t address, uint32_t value, uint32_t count)
    {
        if (address >= bitmap->pages * bitsPerPage)
        {
            uint32_t requiredPages = 1 + address / bitsPerPage;
            resize(bitmap, requiredPages);
        }

        if (value)
        {
            for (size_t i = 0; i < count; i++)
                setBit(bitmap->location, address + i);
        }
        else
        {
            for (size_t i = 0; i < count; i++)
                resetBit(bitmap->location, address + i);
        }
    }

    void setInt(bitmap_t *bitmap, uint32_t index, uint32_t value)
    {
        if (index >= bitmap->pages * intsPerPage)
        {
            uint32_t requiredPages = 1 + index / intsPerPage;
            resize(bitmap, requiredPages);
        }
        bitmap->location[index] = value;
    }

    uint8_t get(bitmap_t *bitmap, uint32_t address)
    {
        return testBit(bitmap->location, address);
    }

    uint32_t getInt(bitmap_t *bitmap, uint32_t index)
    {
        return bitmap->location[index];
    }

} // namespace bitmap