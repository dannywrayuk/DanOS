#pragma once
#include <stddef.h>

namespace slab
{

    void init();

    void *malloc();
    void *malloc(size_t size);
    void *calloc();
    void *calloc(size_t size);
    void free(void *ptr);

} // namespace slab