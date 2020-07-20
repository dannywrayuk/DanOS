#include <common/cstring.h>
#include <common/serial.h>
#include <common/port.h>

void init_serial()
{
    outb(COMPORT1 + 1, 0x00); // Disable all interrupts
    outb(COMPORT1 + 3, 0x80); // Enable DLAB (set baud rate divisor)
    outb(COMPORT1 + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
    outb(COMPORT1 + 1, 0x00); //                  (hi byte)
    outb(COMPORT1 + 3, 0x03); // 8 bits, no parity, one stop bit
    outb(COMPORT1 + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
    outb(COMPORT1 + 4, 0x0B); // IRQs enabled, RTS/DSR set
}

int is_transmit_empty()
{
    return inb(COMPORT1 + 5) & 0x20;
}

void write_serial(char a)
{
    while (is_transmit_empty() == 0)
        ;

    outb(COMPORT1, a);
}

void write_serial(string a)
{
    int x = 0;
    while (a[x] != '\0')
    {
        while (is_transmit_empty() == 0)
            ;
        outb(COMPORT1, a[x]);
        x++;
    }
}
void write_serial(const string a)
{
    write_serial((string)a);
}
