#include <common/string.h>
#include <stdint.h>
#include <logging/debug.h>

#include <common/serial.h>

void dbg(string msg)
{
    write_serial(msg);
}

void dbgc(char msg)
{
    write_serial(msg);
}

void dbg(uint32_t msg)
{
    write_serial(utoa(msg, 16));
}

void endl()
{
    write_serial('\n');
};