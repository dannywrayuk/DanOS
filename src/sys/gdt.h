#pragma once
#include <stdint.h>

namespace sys
{

    struct gdt_entry
    {
        uint16_t limit_low;  // The lower 16 bits of the limit.
        uint16_t base_low;   // The lower 16 bits of the base.
        uint8_t base_middle; // The next 8 bits of the base.
        uint8_t access;      // Access flags, determine what ring this segment can be used in.
        uint8_t granularity;
        uint8_t base_high; // The last 8 bits of the base.
    } __attribute__((packed));

    struct tss_entry
    {
        uint16_t length;
        uint16_t base_low16;
        uint8_t base_mid8;
        uint8_t flags1;
        uint8_t flags2;
        uint8_t base_high8;
        uint32_t base_upper32;
        uint32_t reserved;
    } __attribute__((packed));

    struct gdt
    {
        struct gdt_entry entries[5];
        struct tss_entry tss;
    } __attribute__((packed));

    struct gdt_pointer
    {
        uint16_t size;
        uint64_t address;
    } __attribute__((packed));

    void initGDT();

} // namespace sys