#include <build/optional.h>
#include <stdint.h>
#include <common/serial.h>
#include <logging/debug.h>
#include <common/std/stdio.h>

#define MULTIBOOT_MAGIC 0x2BADB002

extern "C" void KMAIN(uint32_t magic, uint32_t addr)
{
    // Check Multiboot Magic
    if (magic != MULTIBOOT_MAGIC)
    {
        return;
    }
    init_serial();
    std::printf("Serial initialised.\n");
#ifdef _BUILD_WITH_TEST
    test_all();
#endif
}