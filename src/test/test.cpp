#include <common/cstring.h>
#include <test/test.h>
#include <logging/debug.h>
#include <logging/ansi_colours.h>

string reason;

void fail_message(string msg)
{
    reason = msg;
}

int test(int passing, const string name)
{
    if (passing)
    {
        dbg(ANSI_COLOUR_BACKGROUND_GREEN);
        dbg(ANSI_BOLD);
        dbg(" PASS ");
        dbg(ANSI_RESET);
        dbg(" ");
        dbg(name);
        endl();
    }
    else
    {
        dbg(ANSI_COLOUR_BACKGROUND_RED);
        dbg(ANSI_BOLD);
        dbg(" FAIL ");
        dbg(ANSI_RESET);
        dbg(" ");
        dbg(name);
        endl();
        dbg(ANSI_COLOUR_BACKGROUND_BLUE);
        dbg(ANSI_BOLD);
        dbg(" REASON ");
        dbg(ANSI_RESET);
        dbg(" ");
        dbg(reason);
        endl();
    }
    return passing;
}

int complete(int result, const string name)
{
    if (result)
    {
        endl();
        dbg(ANSI_COLOUR_BACKGROUND_GREEN);
        dbg(ANSI_BOLD);
        dbg(" PASS ");
        dbg(ANSI_COLOUR_BACKGROUND_BLUE);
        dbg(ANSI_BOLD);
        dbg(" ");
        dbg(name);
        dbg(" ");
        dbg(ANSI_RESET);
        endl();
    }
    else
    {
        endl();
        dbg(ANSI_COLOUR_BACKGROUND_RED);
        dbg(ANSI_BOLD);
        dbg(" FAIL ");
        dbg(ANSI_COLOUR_BACKGROUND_BLUE);
        dbg(ANSI_BOLD);
        dbg(" ");
        dbg(name);
        dbg(" ");
        dbg(ANSI_RESET);
        endl();
    }
    return result;
}
