#include <io/serial.h>
#include <io/port.h>
#include <std/cstdio.h>

#include <io/ansi_colours.h>

#define COMPORT1 0x3f8

namespace serial
{
    int isTransmitEmpty()
    {
        return io::inb(COMPORT1 + 5) & 0x20;
    }

    void out(char a)
    {
        while (isTransmitEmpty() == 0)
            ;
        io::outb(COMPORT1, a);
    }

    void out(const char *a)
    {
        out((char *)a);
    }

    void out(char *a)
    {
        int x = 0;
        while (a[x] != '\0')
        {
            out(a[x]);
            x++;
        }
    }
    void outN(char *a, size_t num)
    {
        int x = 0;
        while (a[x] != '\0' && x < num)
        {
            out(a[x]);
            x++;
        }
    }
    void init()
    {
        io::outb(COMPORT1 + 1, 0x00); // Disable all interrupts
        io::outb(COMPORT1 + 3, 0x80); // Enable DLAB (set baud rate divisor)
        io::outb(COMPORT1 + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
        io::outb(COMPORT1 + 1, 0x00); //                  (hi byte)
        io::outb(COMPORT1 + 3, 0x03); // 8 bits, no parity, one stop bit
        io::outb(COMPORT1 + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
        io::outb(COMPORT1 + 4, 0x0B); // IRQs enabled, RTS/DSR set
        std::printf(" %Cg✓%C0  Serial Logging.\n");
    }

} // namespace serial
