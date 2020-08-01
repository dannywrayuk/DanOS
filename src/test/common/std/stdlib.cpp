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
    if (std::atold(basic_float) != 2.4E11L)
    {
        TEST_FAIL("1: failed basic float converstion");
    }
    if (std::atold(basic_negative_float) != -2.4E11L)
    {
        TEST_FAIL("2: failed basic negative float converstion");
    }
    if (std::atold(small_float) != 2.9E-20L)
    {
        TEST_FAIL("3: failed small float converstion");
    }
    if (std::atold(spaced_float) != 2.9E-20L)
    {
        TEST_FAIL("4: failed spaced float converstion");
    }
    if (std::atold(with_string_float) != 2.9E-20L)
    {
        TEST_FAIL("5: failed float with string converstion");
    }
    if (std::atold(nan) != 0L)
    {
        TEST_FAIL("6: failed nan converstion");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(atof)
{
    if (std::atof(basic_float) != 2.4E11)
    {
        TEST_FAIL("1: failed basic float converstion");
    }
    if (std::atof(basic_negative_float) != -2.4E11)
    {
        TEST_FAIL("2: failed basic negative float converstion");
    }
    if (std::atof(small_float) != 2.9E-20)
    {
        TEST_FAIL("3: failed small float converstion");
    }
    if (std::atof(spaced_float) != 2.9E-20)
    {
        TEST_FAIL("4: failed spaced float converstion");
    }
    if (std::atof(with_string_float) != 2.9E-20)
    {
        TEST_FAIL("5: failed float with string converstion");
    }
    if (std::atof(nan) != 0)
    {
        TEST_FAIL("6: failed nan converstion");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(atoi)
{
    if (std::atoi(basic) != 120)
    {
        TEST_FAIL("1: failed basic int converstion");
    }
    if (std::atoi(negative) != -420)
    {
        TEST_FAIL("2: failed basic negative int converstion");
    }
    if (std::atoi(spaced_basic) != 420)
    {
        TEST_FAIL("3: failed spaced int converstion");
    }
    if (std::atoi(spaced_negative) != -420)
    {
        TEST_FAIL("4: failed spaced negative int converstion");
    }
    if (std::atoi(with_string) != 420)
    {
        TEST_FAIL("5: failed int with string converstion");
    }
    if (std::atoi(nan) != 0)
    {
        TEST_FAIL("6: failed nan converstion");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(atol)
{
    if (std::atol(basic) != 120L)
    {
        TEST_FAIL("1: failed basic int converstion");
    }
    if (std::atol(negative) != -420L)
    {
        TEST_FAIL("2: failed basic negative int converstion");
    }
    if (std::atol(spaced_basic) != 420L)
    {
        TEST_FAIL("3: failed spaced int converstion");
    }
    if (std::atol(spaced_negative) != -420L)
    {
        TEST_FAIL("4: failed spaced negative int converstion");
    }
    if (std::atol(with_string) != 420L)
    {
        TEST_FAIL("5: failed int with string converstion");
    }
    if (std::atol(nan) != 0L)
    {
        TEST_FAIL("6: failed nan converstion");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(atoll)
{
    if (std::atoll(basic) != 120LL)
    {
        TEST_FAIL("1: failed basic int converstion");
    }
    if (std::atoll(negative) != -420LL)
    {
        TEST_FAIL("2: failed basic negative int converstion");
    }
    if (std::atoll(spaced_basic) != 420LL)
    {
        TEST_FAIL("3: failed spaced int converstion");
    }
    if (std::atoll(spaced_negative) != -420LL)
    {
        TEST_FAIL("4: failed spaced negative int converstion");
    }
    if (std::atoll(with_string) != 420LL)
    {
        TEST_FAIL("5: failed int with string converstion");
    }
    if (std::atoll(nan) != 0LL)
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
    if (std::strtold(basic_float, &end) != 2.4E11L)
    {
        TEST_FAIL("1: failed basic float converstion");
    }
    if (end != &basic_float[6])
    {
        TEST_FAIL("2: failed endpointer");
    }
    if (std::strtold(basic_negative_float, &end) != -2.4E11L)
    {
        TEST_FAIL("3: failed basic negative float converstion");
    }
    if (std::strtold(small_float, &end) != 2.9E-20L)
    {
        TEST_FAIL("4: failed small float converstion");
    }
    if (std::strtold(spaced_float, &end) != 2.9E-20L)
    {
        TEST_FAIL("5: failed spaced float converstion");
    }
    if (std::strtold(with_string_float, &end) != 2.9E-20L)
    {
        TEST_FAIL("6: failed float with string converstion");
    }
    if (end != &with_string_float[11])
    {
        TEST_FAIL("7: failed endpointer");
    }
    if (std::strtold(nan, &end) != 0L)
    {
        TEST_FAIL("8: failed nan converstion");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strtoll)
{
    char *end;
    if (std::strtoll(basic, &end, 10) != 120L)
    {
        TEST_FAIL("1: failed basic int converstion");
    }
    if (end != &basic[3])
    {
        TEST_FAIL("2: failed endpointer");
    }
    if (std::strtoll(negative, &end, 10) != -420L)
    {
        TEST_FAIL("3: failed basic negative int converstion");
    }
    if (std::strtoll(spaced_basic, &end, 10) != 420L)
    {
        TEST_FAIL("4: failed spaced int converstion");
    }
    if (std::strtoll(spaced_negative, &end, 10) != -420L)
    {
        TEST_FAIL("5: failed spaced negative int converstion");
    }
    if (std::strtoll(with_string, &end, 10) != 420L)
    {
        TEST_FAIL("6: failed int with string converstion");
    }
    if (end != &with_string[8])
    {
        TEST_FAIL("7: failed endpointer");
    }
    if (std::strtoll(nan, &end, 10) != 0L)
    {
        TEST_FAIL("8: failed nan converstion");
    }
    if (std::strtoll(basic, &end, 0) != 120L)
    {
        TEST_FAIL("9: failed decimal base detection");
    }
    if (std::strtoll(binary, &end, 0) != 0b1001L)
    {
        TEST_FAIL("10: failed binary base detection");
    }
    if (std::strtoll(octal, &end, 0) != 010L)
    {
        TEST_FAIL("11: failed octal base detection");
    }
    if (std::strtoll(hex, &end, 0) != 0x1abcL)
    {
        TEST_FAIL("12: failed hex base detection");
    }
    if (std::strtoll(hex_negative, &end, 0) != -0x1abcL)
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
    if (std::strtoull(basic, &end, 10) != 120UL)
    {
        TEST_FAIL("1: failed basic int converstion");
    }
    if (end != &basic[3])
    {
        TEST_FAIL("2: failed endpointer");
    }
    if (std::strtoull(negative, &end, 10) != 0)
    {
        TEST_FAIL("3: failed basic negative int converstion");
    }
    if (std::strtoull(spaced_basic, &end, 10) != 420UL)
    {
        TEST_FAIL("4: failed spaced int converstion");
    }
    if (std::strtoull(spaced_negative, &end, 10) != 0)
    {
        TEST_FAIL("5: failed spaced negative int converstion");
    }
    if (std::strtoull(with_string, &end, 10) != 420UL)
    {
        TEST_FAIL("6: failed int with string converstion");
    }
    if (end != &with_string[8])
    {
        TEST_FAIL("7: failed endpointer");
    }
    if (std::strtoull(nan, &end, 10) != 0UL)
    {
        TEST_FAIL("8: failed nan converstion");
    }
    if (std::strtoll(basic, &end, 0) != 120L)
    {
        TEST_FAIL("9: failed decimal base detection");
    }
    if (std::strtoll(binary, &end, 0) != 0b1001L)
    {
        TEST_FAIL("10: failed binary base detection");
    }
    if (std::strtoll(octal, &end, 0) != 010L)
    {
        TEST_FAIL("11: failed octal base detection");
    }
    if (std::strtoll(hex, &end, 0) != 0x1abcL)
    {
        TEST_FAIL("12: failed hex base detection");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(rand)
{
    int k = std::rand() % 10 + 1;

    if (k < 1 || k > 10)
    {
        TEST_FAIL("1: random out of range");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(srand)
{
    std::srand(1);
    int k = std::rand() % 10 + 1;

    if (k != 9)
    {
        TEST_FAIL("1: seed not the same");
    }
    k = std::rand() % 10 + 1;
    if (k != 7)
    {
        TEST_FAIL("2: seed not the same");
    }
    k = std::rand() % 10 + 1;
    if (k != 4)
    {
        TEST_FAIL("3: seed not the same");
    }
}
END_IMPLEMENT

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
BEGIN_IMPLEMENT(bsearch)
{
    int values[] = {50, 20, 60, 40, 10, 30};
    int *pItem;
    int key = 40;
    std::qsort(values, 6, sizeof(int), compare);
    pItem = (int *)std::bsearch(&key, values, 6, sizeof(int), compare);
    if (*pItem != key)
    {
        TEST_FAIL("did not find key in list.");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(qsort)
{

    int values[] = {40, 10, 100, 90, 20, 25};
    int sorted_values[] = {10, 20, 25, 40, 90, 100};
    std::qsort(values, 6, sizeof(int), compare);
    for (int n = 0; n < 6; n++)
    {
        if (values[n] != sorted_values[n])
        {
            TEST_FAIL("1: values incorrectly sorted.");
        }
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(abs)
{
    int n = -10;
    int np = 10;
    long int nl = -10;
    long long int nll = -10;

    if (std::abs(n) < 0)
    {
        TEST_FAIL("1: failed to change sign");
    }
    if (std::abs(np) < 0)
    {
        TEST_FAIL("2: changed wrong sign");
    }
    if (std::abs(nl) < 0)
    {
        TEST_FAIL("3: failed to change sign");
    }
    if (std::abs(nll) < 0)
    {
        TEST_FAIL("4: failed to change sign");
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
    TEST(rand);
    TEST(srand);
    TEST(bsearch);
    TEST(qsort);
    TEST(abs);
}
END_TESTS