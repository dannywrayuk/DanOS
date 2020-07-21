#pragma once
#include <common/cstring.h>

#define TEST(name)                            \
    if (!test(name##_test_function(), #name)) \
    {                                         \
        pass = 0;                             \
    }

#define TEST_IMPLEMENT(name) int name##_test_function()
#define BEGIN_TESTS(name)      \
    int name##_test_function() \
    {                          \
        int pass = 1;

#define END_TESTS \
    return pass;  \
    }

#define TEST_PASS return 1

#define TEST_FAIL(msg) \
    fail_message(msg); \
    return 0

#define TEST_ENTRY(name) \
    int test_##name() { return complete(name##_test_function(), #name); }

#define DEFINE_TEST_FUNCTIONS(name) \
    int name##_test_function();     \
    int test_##name();

#define TEST_DEBUG(msg) test_debug_message(msg)

#define LABEL_PASS dbg_label(" PASS ", ANSI_COLOUR_BACKGROUND_GREEN)
#define LABEL_FAIL dbg_label(" FAIL ", ANSI_COLOUR_BACKGROUND_RED)
#define LABEL_DEBUG dbg_label(" DEBUG", ANSI_COLOUR_BACKGROUND_CYAN)
#define LABEL_REASON dbg_label("REASON", ANSI_COLOUR_BACKGROUND_BLUE)
#define LABEL_OTHER(msg) dbg_label(msg, ANSI_COLOUR_BACKGROUND_MAGENTA)

void fail_message(const string msg);
void test_debug_message(const string msg);
int test(int passing, const string name);
int complete(int result, const string name);
