#include <stdint.h>
#include <common/serial.h>
#include <logging/debug.h>
#include <logging/ansi_colours.h>
// #include <test/all.h>

#define MULTIBOOT_MAGIC 0x2BADB002

extern "C" void KMAIN(uint32_t magic, uint32_t addr)
{
    // Check Multiboot Magic
    if (magic != MULTIBOOT_MAGIC)
    {
        return;
    }
    init_serial();
    dbg("Serial initialised.\n");
    endl();
}