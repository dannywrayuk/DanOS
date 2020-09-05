#include <common/serial.h>
#include <common/port.h>

namespace io
{
    void initSerial()
    {
        io::outb(COMPORT1 + 1, 0x00); // Disable all interrupts
        io::outb(COMPORT1 + 3, 0x80); // Enable DLAB (set baud rate divisor)
        io::outb(COMPORT1 + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
        io::outb(COMPORT1 + 1, 0x00); //                  (hi byte)
        io::outb(COMPORT1 + 3, 0x03); // 8 bits, no parity, one stop bit
        io::outb(COMPORT1 + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
        io::outb(COMPORT1 + 4, 0x0B); // IRQs enabled, RTS/DSR set
    }

    int isTransmitEmpty()
    {
        return io::inb(COMPORT1 + 5) & 0x20;
    }

    void serialOut(char a)
    {
        while (isTransmitEmpty() == 0)
            ;
        io::outb(COMPORT1, a);
    }

    void serialOut(const char *a)
    {
        serialOut((char *)a);
    }

    void serialOut(char *a)
    {
        int x = 0;
        while (a[x] != '\0')
        {
            serialOut(a[x]);
            x++;
        }
    }
    void serialnOut(char *a, size_t num)
    {
        int x = 0;
        while (a[x] != '\0' && x < num)
        {
            serialOut(a[x]);
            x++;
        }
    }
} // namespace io
