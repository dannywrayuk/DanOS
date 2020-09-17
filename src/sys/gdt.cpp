#include <sys/gdt.h>
#include <std/cstdio.h>

namespace sys
{

    static struct gdt gdt;
    static struct gdt_pointer gdt_pointer;

    void gdtSetGate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
    {
        gdt.entries[num].base_low = (base & 0xFFFF);
        gdt.entries[num].base_middle = (base >> 16) & 0xFF;
        gdt.entries[num].base_high = (base >> 24) & 0xFF;

        gdt.entries[num].limit_low = (limit & 0xFFFF);
        gdt.entries[num].granularity = (limit >> 16) & 0x0F;

        gdt.entries[num].granularity |= gran & 0xF0;
        gdt.entries[num].access = access;
    }

    void gdtSetTSS(uint16_t length, uint8_t flags)
    {
        gdt.tss.length = length;
        gdt.tss.base_low16 = 0;
        gdt.tss.base_mid8 = 0;
        gdt.tss.flags1 = flags;
        gdt.tss.flags2 = 0;
        gdt.tss.base_high8 = 0;
        gdt.tss.base_upper32 = 0;
        gdt.tss.reserved = 0;
    }

    void initGDT()
    {
        gdt_pointer.size = sizeof(gdt) - 1;
        gdt_pointer.address = (uint64_t)&gdt;

        gdtSetGate(0, 0, 0, 0, 0);       // Null segment
        gdtSetGate(1, 0, 0, 0x9A, 0x20); // Code segment
        gdtSetGate(2, 0, 0, 0x92, 0);    // Data segment
        gdtSetGate(3, 0, 0, 0xF2, 0);    // User mode code segment
        gdtSetGate(4, 0, 0, 0xFA, 0x20); // User mode data segment
        gdtSetTSS(0x68, 0x89);           // TSS segment

        asm volatile(
            "lgdt %0\n\t"
            "push rbp\n\t"
            "mov rbp, rsp\n\t"
            "push %1\n\t"
            "push rbp\n\t"
            "pushfq\n\t"
            "push %2\n\t"
            "push OFFSET 1f\n\t"
            "iretq\n\t"
            "1:\n\t"
            "pop rbp\n\t"
            "mov ds, %1\n\t"
            "mov es, %1\n\t"
            "mov fs, %1\n\t"
            "mov gs, %1\n\t"
            "mov ss, %1\n\t"
            :
            : "m"(gdt_pointer), "r"((uint64_t)0x10), "r"((uint64_t)0x08)
            : "memory");
        std::printf("GDT\t\t✓\n");
    }
} // namespace sys