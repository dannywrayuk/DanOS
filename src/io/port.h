#pragma once
#include <stdint.h>

namespace io
{
    uint8_t inb(uint16_t port);

    void outb(uint16_t port, uint8_t data);

} // namespace io
