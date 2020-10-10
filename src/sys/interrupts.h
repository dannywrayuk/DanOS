#pragma once
typedef void (*handlerFunction)();

namespace sys
{

    void registerinterruptHandler(int interrupt, handlerFunction handler);

} // namespace sys

#define IRQ(x) extern "C" void irq##x##Handler();
IRQ(0);
IRQ(1);
#undef IRQ