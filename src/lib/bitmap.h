#pragma once
#include <stdint.h>

struct bitmap_t
{
    uint32_t *location;
    uint32_t pages = 0;
};

namespace bitmap
{
    const uint32_t bytesPerPage = 0x1000;
    const uint32_t bitsPerPage = 0x8000;
    const uint32_t intsPerPage = 0x400;

    bitmap_t *create();
    bitmap_t *create(uint32_t initalPages);
    bitmap_t *create(void *base, uint32_t initialPages);

    void resize(bitmap_t *bitmap, uint32_t requiredPages);

    uint8_t get(bitmap_t *bitmap, uint32_t address);
    uint32_t getInt(bitmap_t *bitmap, uint32_t index);

    void set(bitmap_t *bitmap, uint32_t address, uint32_t value);
    void set(bitmap_t *bitmap, uint32_t address, uint32_t value, uint32_t count);
    void setInt(bitmap_t *bitmap, uint32_t index, uint32_t value);

    void destroy(bitmap_t *bitmap);

} // namespace bitmap