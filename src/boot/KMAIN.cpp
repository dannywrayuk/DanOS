#include <stdint.h>
#include <io/serial.h>
#include <std/cstdio.h>

#define MULTIBOOT_MAGIC 0x2BADB002

extern "C" void KMAIN(uint32_t magic, uint32_t addr)
{
    // Check Multiboot Magic
    if (magic != MULTIBOOT_MAGIC)
    {
        return;
    }
    io::initSerial();
    std::printf("Serial initialised.\n");
}