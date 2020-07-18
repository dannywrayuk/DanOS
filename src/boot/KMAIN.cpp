#include <common/stdint.h>

#define MULTIBOOT_MAGIC 0x1BADB002

extern "C" void KMAIN(uint32_t magic, uint32_t addr)
{

    // Check Multiboot Magic
    if (magic != MULTIBOOT_MAGIC)
    {
        return;
    }

    while (1)
    {
    }
}