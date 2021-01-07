#pragma once
#include <stdint.h>

namespace interrupt
{
    typedef void (*handlerFunction)();

    void registerHandler(uint8_t interrupt, handlerFunction handler);

} // namespace interrupt

#define IRQ(x) extern "C" void irq##x##Handler();
IRQ(0);
IRQ(1);
#undef IRQ