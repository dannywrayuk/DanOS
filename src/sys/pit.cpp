
#include <sys/pit.h>
#include <io/port.h>
#include <sys/pic.h>
#include <std/cstdio.h>
#include <sys/interrupts.h>

uint64_t t = 0;
uint16_t freq = 200;

extern "C" void tick_handler()
{
    t++;
}

namespace pit
{
    uint64_t getTicks()
    {
        return t;
    }

    void setFreq(uint16_t f)
    {
        freq = f;
        uint32_t reset = 1193182 / freq;
        if ((1193182 % freq) > (freq / 2))
            reset++;
        if (reset > 0xFFFF)
            reset = 0xFFFF;
        if (reset < 0x3)
            reset = 0x3;

        uint8_t low = reset & 0xff;
        uint8_t high = (reset >> 8) & 0xff;

        io::outb(0x40, low);
        io::wait();
        io::outb(0x40, high);
        io::wait();
    }

    void init()
    {
        io::outb(0x43, 0x36);
        io::wait();
        setFreq(0xc8);
        interrupt::registerHandler(0x0, tick_handler);
        pic::setMask(0x00, 0x00);
    }

} // namespace pit
