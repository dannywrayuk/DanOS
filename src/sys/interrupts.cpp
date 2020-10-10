#include <sys/interrupts.h>
#include <sys/pic.h>
#include <std/cstdio.h>

sys::interrupt::handlerFunction handlers[0xff];

extern "C" void interruptHandler(uint8_t interrupt)
{
    if (handlers[interrupt])
    {
        sys::interrupt::handlerFunction handler = handlers[interrupt];
        handler();
    }

    sys::pic::EOI(interrupt);
}

namespace sys
{
    namespace interrupt
    {
        void registerHandler(uint8_t interrupt, handlerFunction handler)
        {
            handlers[interrupt] = handler;
        }

    } // namespace interrupt

} // namespace sys