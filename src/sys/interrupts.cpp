#include <sys/interrupts.h>
#include <sys/pic.h>
#include <std/cstdio.h>

interrupt::handlerFunction handlers[0xff];

extern "C" void interruptHandler(uint8_t interrupt)
{
    if (handlers[interrupt])
    {
        interrupt::handlerFunction handler = handlers[interrupt];
        handler();
    }

    pic::EOI(interrupt);
}

namespace interrupt
{
    void registerHandler(uint8_t interrupt, handlerFunction handler)
    {
        handlers[interrupt] = handler;
    }

} // namespace interrupt
