#include <stdint.h>
#include <boot/stivale.h>

#include <io/serial.h>

#include <std/cstdio.h>

#include <sys/gdt.h>

extern "C" void KMAIN(struct stivale_struct *bootloader_data)
{
    io::initSerial();
    std::printf("gdtptr location: %#x", sys::getGDTptr());
    sys::initGDT();
    std::printf("hello");

    asm volatile("hlt");
}