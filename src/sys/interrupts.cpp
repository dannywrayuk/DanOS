#include <sys/interrupts.h>
#include <sys/pic.h>
#include <std/cstdio.h>

handlerFunction handlers[0xff];

extern "C" void interruptHandler(int interrupt)
{
    if (interrupt >= 0 && interrupt < 0xff)
    {
        if (handlers[interrupt])
        {
            handlerFunction handler = handlers[interrupt];
            handler();
        }
    }
    sys::picEOI(interrupt);
}

namespace sys
{

    void registerinterruptHandler(int interrupt, handlerFunction handler)
    {
        handlers[interrupt] = handler;
    }

} // namespace sys