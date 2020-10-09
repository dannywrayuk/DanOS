#pragma once
#include <stdint.h>

namespace sys
{

    struct idt_entry
    {
        uint16_t offset_lo;
        uint16_t selector;
        uint8_t ist;
        uint8_t type_attr;
        uint16_t offset_mid;
        uint32_t offset_hi;
        uint32_t zero;
    } __attribute__((packed));

    struct idt_pointer
    {
        uint16_t size;
        uint64_t address;
    } __attribute__((packed));

    void initIDT();

} // namespace sys