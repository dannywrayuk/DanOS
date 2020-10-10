#include <sys/pic.h>
#include <io/port.h>

#include <std/cstdio.h>

#define CMD_INIT 0x11
#define MODE_8086 0x01

namespace sys
{
    namespace pic
    {
        void EOI(uint8_t vec)
        {
            if (vec >= 8)
            {
                io::outb(0xa0, 0x20);
            }
            io::outb(0x20, 0x20);
        }

        void remap(uint8_t pic0_offset, uint8_t pic1_offset)
        {

            /* Save masks */
            uint8_t pic0_mask = io::inb(0x21);
            uint8_t pic1_mask = io::inb(0xa1);

            io::outb(0x20, CMD_INIT);
            io::wait();
            io::outb(0xa0, CMD_INIT);
            io::wait();

            io::outb(0x21, pic0_offset);
            io::wait();
            io::outb(0xa1, pic1_offset);
            io::wait();

            io::outb(0x21, 0x04);
            io::wait();
            io::outb(0xa1, 0x02);
            io::wait();

            io::outb(0x21, MODE_8086);
            io::wait();
            io::outb(0xa1, MODE_8086);
            io::wait();

            /* Restore masks */
            io::outb(0x21, pic0_mask);
            io::wait();
            io::outb(0xa1, pic1_mask);
            io::wait();
        }

        void setMask(uint8_t line, int status)
        {
            uint16_t port;
            uint8_t value;

            if (line < 8)
            {
                port = 0x21;
            }
            else
            {
                port = 0xa1;
                line -= 8;
            }

            if (!status)
                value = io::inb(port) & ~((uint8_t)1 << line);
            else
                value = io::inb(port) | ((uint8_t)1 << line);

            io::outb(port, value);
            io::wait();
        }

        void maskAll()
        {
            io::outb(0xa1, 0xff);
            io::outb(0x21, 0xff);
        }

        void init()
        {
            remap(0x21, 0x28);
            maskAll();
            setMask(0x01, 0x00);
            std::printf(" %Cg✓%C0  PIC.\n");
        }

    } // namespace pic

} // namespace sys
