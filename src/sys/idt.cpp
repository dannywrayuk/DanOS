#include <sys/idt.h>
#include <mem/cmem.h>
#include <io/port.h>
#include <sys/exceptions.h>
#include <sys/interrupts.h>

#include <std/cstdio.h>
#include <sys/pic.h>
#include <sys/pit.h>

extern "C" void key_handler()
{
    uint8_t status = io::inb(0x64);
    if (status & 0x01)
    {
        int8_t keycode = io::inb(0x60);
        if (keycode > 0)
        {
            std::printf("keypress\n");
        }
    }
}

namespace sys
{
    namespace idt
    {
        static struct entry idt[0x100];
        static struct pointer pointer;

        void registerInterrupt(uint8_t num, void (*handler)(), uint8_t ist, uint8_t type)
        {
            uint64_t p = (uint64_t)handler;

            idt[num].offset_lo = (uint16_t)p;
            idt[num].selector = 0x08;
            idt[num].ist = ist;
            idt[num].type_attr = type;
            idt[num].offset_mid = (uint16_t)(p >> 16);
            idt[num].offset_hi = (uint32_t)(p >> 32);
            idt[num].zero = 0;
        }

        void init()
        {
            pointer.size = sizeof(idt) - 1;
            pointer.address = (uint64_t)&idt;

            memset(&idt, 0, sizeof(idt));
#define ISR(x) isr##x##Handler
#define RegisterISR(x, ist) registerInterrupt(x, ISR(x), ist, 0x8e);
            RegisterISR(0, 0);
            RegisterISR(1, 0);
            RegisterISR(2, 0);
            RegisterISR(3, 0);
            RegisterISR(4, 0);
            RegisterISR(5, 0);
            RegisterISR(6, 0);
            RegisterISR(7, 0);
            RegisterISR(8, 1);
            RegisterISR(10, 0);
            RegisterISR(11, 0);
            RegisterISR(12, 0);
            RegisterISR(13, 0);
            RegisterISR(14, 0);
            RegisterISR(16, 0);
            RegisterISR(17, 0);
            RegisterISR(18, 0);
            RegisterISR(19, 0);
            RegisterISR(20, 0);
            RegisterISR(30, 0);
#undef ISR
#undef RegisterISR

#define IRQ(x) irq##x##Handler
#define RegisterIRQ(x) registerInterrupt(0x20 + x, IRQ(x), 0, 0x8e);
            RegisterIRQ(0);
            RegisterIRQ(1);
#undef IRQ
#undef RegisterIRQ
            asm volatile(
                "lidt %0"
                :
                : "m"(pointer));

            asm volatile("sti");
            std::printf(" %Cg✓%C0  IDT.\n");
            sys::interrupt::registerHandler(0x1, key_handler);
        }

    } // namespace idt

} // namespace sys
