#include <stdint.h>
#include <boot/stivale.h>

#include <io/serial.h>
#include <sys/gdt.h>
#include <sys/idt.h>
#include <sys/pic.h>
#include <sys/pit.h>

extern "C" void KMAIN(stivale_struct *bootloader_data)
{
    io::serial::init();
    sys::gdt::init();
    sys::idt::init();
    sys::pic::init();
    while (1)
        ;
}