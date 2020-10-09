#include <sys/idt.h>
#include <mem/cmem.h>
#include <io/port.h>
#include <sys/exceptions.h>

#include <std/cstdio.h>
#include <sys/pic.h>
#include <sys/pit.h>

namespace sys
{

    static struct idt_entry idt[256];
    static struct idt_pointer idt_pointer;

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

    void initIDT()
    {
        idt_pointer.size = sizeof(idt) - 1;
        idt_pointer.address = (uint64_t)&idt;

        memset(&idt, 0, sizeof(idt));

        registerInterrupt(0x00, div0_handler, 0, 0x8e);
        registerInterrupt(0x01, debug_handler, 0, 0x8e);
        registerInterrupt(0x02, nmi_handler, 0, 0x8e);
        registerInterrupt(0x03, breakpoint_handler, 0, 0x8e);
        registerInterrupt(0x04, overflow_handler, 0, 0x8e);
        registerInterrupt(0x05, bound_range_handler, 0, 0x8e);
        registerInterrupt(0x06, inv_opcode_handler, 0, 0x8e);
        registerInterrupt(0x07, no_dev_handler, 0, 0x8e);
        registerInterrupt(0x08, double_fault_handler, 1, 0x8e);
        registerInterrupt(0x0a, inv_tss_handler, 0, 0x8e);
        registerInterrupt(0x0b, no_segment_handler, 0, 0x8e);
        registerInterrupt(0x0c, ss_fault_handler, 0, 0x8e);
        registerInterrupt(0x0d, gpf_handler, 0, 0x8e);
        registerInterrupt(0x0e, page_fault_handler, 0, 0x8e);
        registerInterrupt(0x10, x87_fp_handler, 0, 0x8e);
        registerInterrupt(0x11, alignment_check_handler, 0, 0x8e);
        registerInterrupt(0x12, machine_check_handler, 0, 0x8e);
        registerInterrupt(0x13, simd_fp_handler, 0, 0x8e);
        registerInterrupt(0x14, virt_handler, 0, 0x8e);
        registerInterrupt(0x1e, security_handler, 0, 0x8e);

        registerInterrupt(0x20, irq0_handler, 0, 0x8e);
        registerInterrupt(0x21, irq1_handler, 0, 0x8e);

        asm volatile(
            "lidt %0"
            :
            : "m"(idt_pointer));

        asm volatile("sti");
        std::printf(" %Cg✓%C0  IDT.\n");
    }

} // namespace sys

extern "C" void key_handler()
{
    sys::picEOI(0x20);
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
