#include <common/std/cstring.h>
#include <test/test.h>
#include <logging/debug.h>
#include <logging/ansi_colours.h>

string test_name;

void fail_message()
{
}

void fail_message(const string msg)
{
    LABEL_FAIL;
    LABEL_REASON;
    dbg(test_name);
    dbg(msg);
    endl();
}

void test_debug_message(const string msg)
{
    LABEL_DEBUG;
    dbg(msg);
    endl();
}

int test(int (*function)(), const string name)
{
    test_name = (string)name;
    int passing = function();
    passing
        ? LABEL_PASS
        : LABEL_FAIL;
    dbg(name);
    endl();
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
