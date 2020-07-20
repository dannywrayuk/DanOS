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

void fail_message(string msg);
int test(int passing, const string name);
int complete(int result, const string name);
