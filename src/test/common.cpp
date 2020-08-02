#include <test/test.h>
#include <test/common/std/cstring.h>
#include <test/common/std/ctype.h>
#include <test/common/std/stdlib.h>
#include <test/common/std/stdio.h>

BEGIN_TESTS(common)
{
    TEST(cstring);
    TEST(ctype);
    TEST(stdlib);
    TEST(stdio);
}
END_TESTS

TEST_ENTRY(common)