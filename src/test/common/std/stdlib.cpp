#include <test/test.h>
#include <common/std/stdlib.h>
#include <logging/debug.h>

// Test Strings
const char *basic = "120";
const char *negative = "-420";
const char *spaced_basic = "     420   ";
const char *spaced_negative = "     -420   ";
const char *with_string = "     420hello";
const char *nan = "     hello   ";
const char *basic_float = "2.4E11";
const char *basic_negative_float = "-2.4E11";
const char *small_float = "2.9E-20";
const char *spaced_float = "    2.9E-20  ";
const char *with_string_float = "    2.9E-20hello";
const char *binary = "  0b1001";
const char *octal = "  010";
const char *hex = "  0x1abc";
const char *hex_negative = "  -0x1abc";

BEGIN_IMPLEMENT(atold)
{
    if (atold(basic_float) != 2.4E11L)
    {
        TEST_FAIL("1: failed basic float converstion");
    }
    if (atold(basic_negative_float) != -2.4E11L)
    {
        TEST_FAIL("2: failed basic negative float converstion");
    }
    if (atold(small_float) != 2.9E-20L)
    {
        TEST_FAIL("3: failed small float converstion");
    }
    if (atold(spaced_float) != 2.9E-20L)
    {
        TEST_FAIL("4: failed spaced float converstion");
    }
    if (atold(with_string_float) != 2.9E-20L)
    {
        TEST_FAIL("5: failed float with string converstion");
    }
    if (atold(nan) != 0L)
    {
        TEST_FAIL("6: failed nan converstion");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(atof)
{
    if (atof(basic_float) != 2.4E11)
    {
        TEST_FAIL("1: failed basic float converstion");
    }
    if (atof(basic_negative_float) != -2.4E11)
    {
        TEST_FAIL("2: failed basic negative float converstion");
    }
    if (atof(small_float) != 2.9E-20)
    {
        TEST_FAIL("3: failed small float converstion");
    }
    if (atof(spaced_float) != 2.9E-20)
    {
        TEST_FAIL("4: failed spaced float converstion");
    }
    if (atof(with_string_float) != 2.9E-20)
    {
        TEST_FAIL("5: failed float with string converstion");
    }
    if (atof(nan) != 0)
    {
        TEST_FAIL("6: failed nan converstion");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(atoi)
{
    if (atoi(basic) != 120)
    {
        TEST_FAIL("1: failed basic int converstion");
    }
    if (atoi(negative) != -420)
    {
        TEST_FAIL("2: failed basic negative int converstion");
    }
    if (atoi(spaced_basic) != 420)
    {
        TEST_FAIL("3: failed spaced int converstion");
    }
    if (atoi(spaced_negative) != -420)
    {
        TEST_FAIL("4: failed spaced negative int converstion");
    }
    if (atoi(with_string) != 420)
    {
        TEST_FAIL("5: failed int with string converstion");
    }
    if (atoi(nan) != 0)
    {
        TEST_FAIL("6: failed nan converstion");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(atol)
{
    if (atol(basic) != 120L)
    {
        TEST_FAIL("1: failed basic int converstion");
    }
    if (atol(negative) != -420L)
    {
        TEST_FAIL("2: failed basic negative int converstion");
    }
    if (atol(spaced_basic) != 420L)
    {
        TEST_FAIL("3: failed spaced int converstion");
    }
    if (atol(spaced_negative) != -420L)
    {
        TEST_FAIL("4: failed spaced negative int converstion");
    }
    if (atol(with_string) != 420L)
    {
        TEST_FAIL("5: failed int with string converstion");
    }
    if (atol(nan) != 0L)
    {
        TEST_FAIL("6: failed nan converstion");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(atoll)
{
    if (atoll(basic) != 120LL)
    {
        TEST_FAIL("1: failed basic int converstion");
    }
    if (atoll(negative) != -420LL)
    {
        TEST_FAIL("2: failed basic negative int converstion");
    }
    if (atoll(spaced_basic) != 420LL)
    {
        TEST_FAIL("3: failed spaced int converstion");
    }
    if (atoll(spaced_negative) != -420LL)
    {
        TEST_FAIL("4: failed spaced negative int converstion");
    }
    if (atoll(with_string) != 420LL)
    {
        TEST_FAIL("5: failed int with string converstion");
    }
    if (atoll(nan) != 0LL)
    {
        TEST_FAIL("6: failed nan converstion");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strtod)
{
    // Not Required
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strtof)
{
    // Not Required
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strtol)
{
    // Not Required
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strtold)
{
    char *end;
    if (strtold(basic_float, &end) != 2.4E11L)
    {
        TEST_FAIL("1: failed basic float converstion");
    }
    if (end != &basic_float[6])
    {
        TEST_FAIL("2: failed endpointer");
    }
    if (strtold(basic_negative_float, &end) != -2.4E11L)
    {
        TEST_FAIL("3: failed basic negative float converstion");
    }
    if (strtold(small_float, &end) != 2.9E-20L)
    {
        TEST_FAIL("4: failed small float converstion");
    }
    if (strtold(spaced_float, &end) != 2.9E-20L)
    {
        TEST_FAIL("5: failed spaced float converstion");
    }
    if (strtold(with_string_float, &end) != 2.9E-20L)
    {
        TEST_FAIL("6: failed float with string converstion");
    }
    if (end != &with_string_float[11])
    {
        TEST_FAIL("7: failed endpointer");
    }
    if (strtold(nan, &end) != 0L)
    {
        TEST_FAIL("8: failed nan converstion");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strtoll)
{
    char *end;
    if (strtoll(basic, &end, 10) != 120L)
    {
        TEST_FAIL("1: failed basic int converstion");
    }
    if (end != &basic[3])
    {
        TEST_FAIL("2: failed endpointer");
    }
    if (strtoll(negative, &end, 10) != -420L)
    {
        TEST_FAIL("3: failed basic negative int converstion");
    }
    if (strtoll(spaced_basic, &end, 10) != 420L)
    {
        TEST_FAIL("4: failed spaced int converstion");
    }
    if (strtoll(spaced_negative, &end, 10) != -420L)
    {
        TEST_FAIL("5: failed spaced negative int converstion");
    }
    if (strtoll(with_string, &end, 10) != 420L)
    {
        TEST_FAIL("6: failed int with string converstion");
    }
    if (end != &with_string[8])
    {
        TEST_FAIL("7: failed endpointer");
    }
    if (strtoll(nan, &end, 10) != 0L)
    {
        TEST_FAIL("8: failed nan converstion");
    }
    if (strtoll(basic, &end, 0) != 120L)
    {
        TEST_FAIL("9: failed decimal base detection");
    }
    if (strtoll(binary, &end, 0) != 0b1001L)
    {
        TEST_FAIL("10: failed binary base detection");
    }
    if (strtoll(octal, &end, 0) != 010L)
    {
        TEST_FAIL("11: failed octal base detection");
    }
    if (strtoll(hex, &end, 0) != 0x1abcL)
    {
        TEST_FAIL("12: failed hex base detection");
    }
    if (strtoll(hex_negative, &end, 0) != -0x1abcL)
    {
        TEST_FAIL("12: failed negative hex base detection");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strtoul)
{
    // Not Required
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strtoull)
{
    char *end;
    if (strtoull(basic, &end, 10) != 120UL)
    {
        TEST_FAIL("1: failed basic int converstion");
    }
    if (end != &basic[3])
    {
        TEST_FAIL("2: failed endpointer");
    }
    if (strtoull(negative, &end, 10) != 0)
    {
        TEST_FAIL("3: failed basic negative int converstion");
    }
    if (strtoull(spaced_basic, &end, 10) != 420UL)
    {
        TEST_FAIL("4: failed spaced int converstion");
    }
    if (strtoull(spaced_negative, &end, 10) != 0)
    {
        TEST_FAIL("5: failed spaced negative int converstion");
    }
    if (strtoull(with_string, &end, 10) != 420UL)
    {
        TEST_FAIL("6: failed int with string converstion");
    }
    if (end != &with_string[8])
    {
        TEST_FAIL("7: failed endpointer");
    }
    if (strtoull(nan, &end, 10) != 0UL)
    {
        TEST_FAIL("8: failed nan converstion");
    }
    if (strtoll(basic, &end, 0) != 120L)
    {
        TEST_FAIL("9: failed decimal base detection");
    }
    if (strtoll(binary, &end, 0) != 0b1001L)
    {
        TEST_FAIL("10: failed binary base detection");
    }
    if (strtoll(octal, &end, 0) != 010L)
    {
        TEST_FAIL("11: failed octal base detection");
    }
    if (strtoll(hex, &end, 0) != 0x1abcL)
    {
        TEST_FAIL("12: failed hex base detection");
    }
}
END_IMPLEMENT

BEGIN_TESTS(stdlib)
{
    TEST(atold);
    TEST(atof);
    TEST(atoi);
    TEST(atol);
    TEST(atoll);
    TEST(strtod);
    TEST(strtof);
    TEST(strtol);
    TEST(strtold);
    TEST(strtoll);
    TEST(strtoul);
    TEST(strtoull);
}
END_TESTS