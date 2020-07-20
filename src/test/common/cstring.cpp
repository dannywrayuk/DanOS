#include <test/test.h>
#include <common/cstring.h>

TEST_IMPLEMENT(memcpy)
{
    TEST_PASS;
}

TEST_IMPLEMENT(memmove)
{
    TEST_PASS;
}

BEGIN_TESTS(cstring)
{
    TEST(memcpy);
    TEST(memmove);
}
END_TESTS
