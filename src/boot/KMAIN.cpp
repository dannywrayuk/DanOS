#include <stdint.h>
#include <boot/stivale.h>

#include <io/serial.h>

#include <std/cstdio.h>

static char stack[4096] = {0};

extern "C" void KMAIN(struct stivale_struct *bootloader_data)
{
    io::initSerial();
}