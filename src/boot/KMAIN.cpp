#include <stdint.h>
#include <boot/stivale.h>

#include <io/serial.h>

extern "C" void KMAIN(struct stivale_struct *bootloader_data)
{
    io::initSerial();
}