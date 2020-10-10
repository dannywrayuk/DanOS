#pragma once
#include <stdint.h>
namespace sys
{
    namespace interrupt
    {
        typedef void (*handlerFunction)();

        void registerHandler(uint8_t interrupt, handlerFunction handler);

    } // namespace interrupt

} // namespace sys

#define IRQ(x) extern "C" void irq##x##Handler();
IRQ(0);
IRQ(1);
#undef IRQ