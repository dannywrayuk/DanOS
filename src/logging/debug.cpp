#include <common/cstring.h>
#include <stdint.h>
#include <logging/debug.h>
#include <logging/ansi_colours.h>

#include <common/serial.h>

void dbg(string msg)
{
    write_serial(msg);
}
void dbg(const string msg)
{
    write_serial(msg);
}

void dbg_label(const string msg, const string col)
{
    dbg(col);
    dbg(ANSI_BOLD);
    dbg(" ");
    dbg(msg);
    dbg(" ");
    dbg(ANSI_RESET);
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