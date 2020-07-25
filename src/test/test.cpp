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

int test(int (*function)(int), const string name, int depth)
{
    test_name = (string)name;
    int passing = function(depth);
    passing
        ? LABEL_PASS
        : LABEL_FAIL;

#ifdef PRETTY_TEST
    char buffer[128] = {};
    for (; depth - 1; depth--)
    {
        std::strcat(buffer, "│  ");
    }
    std::strcat(buffer, "├──");
    dbg(buffer);
#endif
    dbg(name);
    endl();
    return passing;
}

int test(int (*function)(), const string name, int depth)
{
    test_name = (string)name;
    int passing = function();
    passing
        ? LABEL_PASS
        : LABEL_FAIL;
#ifdef PRETTY_TEST
    char buffer[128] = {};
    for (; depth - 1; depth--)
    {
        std::strcat(buffer, "│  ");
    }
    std::strcat(buffer, "┌──");
    dbg(buffer);
#endif
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
        dbg("when running ");
        LABEL_OTHER(name);
        dbg("tests.");
        endl();
    }
    return result;
}
