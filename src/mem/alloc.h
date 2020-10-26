#pragma once
#include <stddef.h>

namespace mem
{
    void *malloc(size_t size);
    void *calloc(size_t size);
    void *realloc(void *ptr, size_t size);
    void free(void *ptr);

} // namespace mem