#include <io/port.h>

namespace io
{

    uint8_t inb(uint16_t _port)
    {
        uint8_t rv;
        __asm __volatile__("inb %1, %0"
                           : "=a"(rv)
                           : "dN"(_port));
        return rv;
    }

    void outb(uint16_t _port, uint8_t _data)
    {
        __asm __volatile__("outb %1, %0"
                           :
                           : "dN"(_port), "a"(_data));
    }

} // namespace io