#include <test/test.h>
#include <common/std/ctype.h>
#include <logging/debug.h>

BEGIN_IMPLEMENT(isalnum)
{
    if (isalnum('!'))
    {
        TEST_FAIL("1: matched incorrect character.");
    }

    if (!isalnum('A') || !isalnum('a') || !isalnum('0'))
    {
        TEST_FAIL("2: didn't match correct character.");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(isalpha)
{
    if (isalpha('!'))
    {
        TEST_FAIL("1: matched incorrect character.");
    }

    if (!isalpha('A') || !isalpha('a'))
    {
        TEST_FAIL("2: didn't match correct character.");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(isblank)
{
    if (isblank('!'))
    {
        TEST_FAIL("1: matched incorrect character.");
    }

    if (!isblank(' ') || !isblank('\t'))
    {
        TEST_FAIL("2: didn't match correct character.");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(iscntrl)
{
    if (iscntrl('!'))
    {
        TEST_FAIL("1: matched incorrect character.");
    }

    if (!iscntrl('\0') || !iscntrl('\t') || !iscntrl('\f'))
    {
        TEST_FAIL("2: didn't match correct character.");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(isdigit)
{
    if (isdigit('!'))
    {
        TEST_FAIL("1: matched incorrect character.");
    }

    if (!isdigit('0') || !isdigit('3') || !isdigit('9'))
    {
        TEST_FAIL("2: didn't match correct character.");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(isgraph)
{
    if (isgraph(' '))
    {
        TEST_FAIL("1: matched incorrect character.");
    }

    if (!isgraph('0') || !isgraph('a') || !isgraph('~'))
    {
        TEST_FAIL("2: didn't match correct character.");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(islower)
{
    if (islower('A'))
    {
        TEST_FAIL("1: matched incorrect character.");
    }

    if (!islower('a') || !islower('g') || !islower('z'))
    {
        TEST_FAIL("2: didn't match correct character.");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(isprint)
{
    if (isprint('\t'))
    {
        TEST_FAIL("1: matched incorrect character.");
    }

    if (!isprint('!') || !isprint('g') || !isprint('~'))
    {
        TEST_FAIL("2: didn't match correct character.");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(ispunct)
{
    if (ispunct('A'))
    {
        TEST_FAIL("1: matched incorrect character.");
    }

    if (!ispunct('!') || !ispunct('#') || !ispunct('~'))
    {
        TEST_FAIL("2: didn't match correct character.");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(isspace)
{
    if (isspace('A'))
    {
        TEST_FAIL("1: matched incorrect character.");
    }

    if (!isspace('\t') || !isspace('\f') || !isspace(' '))
    {
        TEST_FAIL("2: didn't match correct character.");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(isupper)
{
    if (isupper('a'))
    {
        TEST_FAIL("1: matched incorrect character.");
    }

    if (!isupper('A') || !isupper('G') || !isupper('Z'))
    {
        TEST_FAIL("2: didn't match correct character.");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(isxdigit)
{
    if (isxdigit('g'))
    {
        TEST_FAIL("1: matched incorrect character.");
    }

    if (!isxdigit('a') || !isxdigit('1') || !isxdigit('F'))
    {
        TEST_FAIL("2: didn't match correct character.");
    }
}
END_IMPLEMENT

BEGIN_TESTS(ctype)
{
    TEST(isalnum);
    TEST(isalpha);
    TEST(isblank);
    TEST(iscntrl);
    TEST(isdigit);
    TEST(isgraph);
    TEST(islower);
    TEST(isprint);
    TEST(ispunct);
    TEST(isspace);
    TEST(isupper);
    TEST(isxdigit);
}
END_TESTS