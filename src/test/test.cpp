#include <common/cstring.h>
#include <test/test.h>
#include <logging/debug.h>
#include <logging/ansi_colours.h>

string reason;

void fail_message(const string msg)
{
    reason = (char *)msg;
}

void test_debug_message(const string msg)
{
    LABEL_DEBUG;
    dbg(msg);
    endl();
}

int test(int passing, const string name)
{
    if (passing)
    {
        LABEL_PASS;
        dbg(name);
        endl();
    }
    else
    {
        LABEL_FAIL;
        dbg(name);
        endl();
        LABEL_REASON;
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
        LABEL_PASS;
        LABEL_OTHER(name);
        endl();
    }
    else
    {
        endl();
        LABEL_FAIL;
        LABEL_OTHER(name);
        endl();
    }
    return result;
}
