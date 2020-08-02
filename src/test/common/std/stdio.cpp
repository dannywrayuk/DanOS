#include <test/common/std/stdio.h>
#include <common/std/stdio.h>

BEGIN_IMPLEMENT(sprintf)
{
    char buffer[200] = {};
    int i = 69;
    char c = 'd';
    const char *s = "hello";
    const char *result = "yeet %6969100010169105450x45dhello";
    std::sprintf(buffer, "yeet %%%d%i%b%u%o%x%#X%c%s", i, i, i, i, i, i, i, c, s);
    if (std::strcmp(buffer, result))
    {
        TEST_DEBUG(buffer);
        TEST_FAIL("1: incorrect log output");
    }
}
END_IMPLEMENT

BEGIN_TESTS(stdio)
{
    TEST(sprintf);
}
END_TESTS