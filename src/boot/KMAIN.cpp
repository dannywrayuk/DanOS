#include <stdint.h>
#include <boot/stivale.h>

#include <io/serial.h>
#include <sys/gdt.h>

extern "C" void KMAIN(stivale_struct *bootloader_data)
{
    io::initSerial();
    sys::initGDT();

    asm volatile("hlt");
}