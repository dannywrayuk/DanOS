#include <mem/alloc.h>
#include <mem/physical.h>
#include <mem/cmem.h>
#include <std/cstdio.h>

namespace mem
{

    struct metaData_t
    {
        size_t pages;
        size_t size;
    };

    void *malloc(size_t size)
    {
        size_t requiredPages = 1 + (size + sizeof(metaData_t)) / PAGE_SIZE;
        size_t ptr = (size_t)phys::alloc(requiredPages);

        if (!ptr)
        {
            return (void *)0;
        }

        ptr += MEM_PHYS_OFFSET;

        metaData_t *metaData = (metaData_t *)ptr;
        metaData->pages = requiredPages;
        metaData->size = size;
        ptr += sizeof(metaData_t);
        return (void *)ptr;
    }

    void *calloc(size_t size)
    {
        size_t requiredPages = 1 + (size + sizeof(metaData_t)) / PAGE_SIZE;
        char *ptr = (char *)phys::allocz(requiredPages);

        if (!ptr)
        {
            return (void *)0;
        }

        ptr += MEM_PHYS_OFFSET;

        metaData_t *metaData = (metaData_t *)ptr;
        metaData->pages = requiredPages;
        metaData->size = size;
        ptr += sizeof(metaData_t);
        return (void *)ptr;
    }

    void *realloc(void *ptr, size_t newSize)
    {

        if (!ptr)
            return malloc(newSize);
        if (!newSize)
        {
            free(ptr);
            return (void *)0;
        }

        metaData_t *metaData = (metaData_t *)((size_t)ptr - sizeof(metaData_t));

        if ((metaData->size + sizeof(metaData_t)) / PAGE_SIZE == (newSize + sizeof(metaData_t)) / PAGE_SIZE)
        {
            metaData->size = newSize;
            return ptr;
        }

        void *newPtr = malloc(newSize);
        if (newPtr == 0)
            return (void *)0;

        if (metaData->size > newSize)
            memcpy(newPtr, (void *)ptr, newSize);
        else
            memcpy(newPtr, (void *)ptr, metaData->size);

        free(ptr);

        return newPtr;
    }

    void free(void *ptr)
    {
        ptr = (void *)((size_t)ptr - sizeof(metaData_t));
        metaData_t *metaData = (metaData_t *)(ptr);

        ptr = (void *)((size_t)ptr - MEM_PHYS_OFFSET);
        phys::free(ptr, metaData->pages);
    }

} // namespace mem