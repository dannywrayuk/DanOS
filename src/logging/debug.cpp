#include <common/std/cstring.h>
#include <stdint.h>
#include <logging/debug.h>
#include <logging/ansi_colours.h>

#include <common/serial.h>

void dbg(char *msg)
{
    write_serial(msg);
}
void dbg(const char *msg)
{
    write_serial(msg);
}

void dbg_label(const char *msg, const char *col)
{
    dbg(col);
    dbg(BOLD_ANSI);
    dbg(" ");
    dbg(msg);
    dbg(" ");
    dbg(RESET_ANSI);
    dbg(" ");
}

void dbgc(char msg)
{
    write_serial(msg);
}

// void dbg(uint32_t msg)
// {
//     write_serial(utoa(msg, 16));
// }

void endl()
{
    write_serial('\n');
};