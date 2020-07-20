#include <stdint.h>
#include <common/serial.h>
#include <logging/debug.h>

#define MULTIBOOT_MAGIC 0x2BADB002

extern "C" void KMAIN(uint32_t magic, uint32_t addr)
{
    // Check Multiboot Magic
    if (magic != MULTIBOOT_MAGIC)
    {
        return;
    }
    uint8_t a = 0x41;
    init_serial();
    dbg("Serial initialised.\n");
    dbg("Magic:   ");
    dbg(magic);
    endl();
    dbg("Address: ");
    dbg(addr);
    endl();
}