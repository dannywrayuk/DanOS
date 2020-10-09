#include <io/port.h>

namespace io
{

    uint8_t inb(uint16_t port)
    {
        uint8_t rv;
        asm volatile("in al, dx"
                     : "=a"(rv)
                     : "d"(port)
                     :);
        return rv;
    }

    void outb(uint16_t port, uint8_t data)
    {
        asm volatile("out dx, al"
                     :
                     : "a"(data), "d"(port)
                     :);
    }

    void wait()
    {
        io::outb(0x80, 0x00);
    }

} // namespace io