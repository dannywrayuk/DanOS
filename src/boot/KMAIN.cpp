#include <stdint.h>
#include <boot/stivale.h>

#include <io/serial.h>
#include <sys/gdt.h>
#include <sys/idt.h>
#include <sys/pic.h>
#include <sys/pit.h>

#include <mem/physical.h>
#include <mem/virtual.h>

extern "C" void KMAIN(stivale_struct *bootloader_data)
{
    serial::init();
    gdt::init();
    idt::init();
    pic::init();
    phys::init(&bootloader_data->memmap);
    virt::init(&bootloader_data->memmap);
    while (1)
        ;
}