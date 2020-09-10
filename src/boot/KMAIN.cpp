#include <stdint.h>
#include <boot/stivale.h>

#include <io/serial.h>

#include <std/cstdio.h>

extern "C" void KMAIN(struct stivale_struct *bootloader_data)
{
    io::initSerial();
}