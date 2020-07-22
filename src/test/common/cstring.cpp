#include <test/test.h>
#include <common/cstring.h>
#include <logging/debug.h>

TEST_IMPLEMENT(memcpy)
{
    struct
    {
        char property1[16];
        int property2;
    } object, object_copy;

    char property3[16] = "dannywray.co.uk";

    memcpy(object.property1, property3, 16);

    if (strcmp(object.property1, property3) != 0)
    {
        TEST_FAIL("memcpy:1: failed to copy string.");
    }

    object.property2 = 69;
    memcpy(&object_copy, &object, sizeof(object));

    if (object.property2 != object_copy.property2 && strcmp(object_copy.property1, property3) != 0)
    {
        TEST_FAIL("memcpy:2: failed to copy structure.");
    }

    TEST_PASS;
}

TEST_IMPLEMENT(memmove)
{
    char str[] = "memmove can be very useful......";
    char result[] = "memmove can be very very useful.";

    memmove(str + 20, str + 15, 11);
    if (strcmp(str, result) != 0)
    {
        TEST_FAIL("memmove:1: failed to move string.");
    }
    TEST_PASS;
}

TEST_IMPLEMENT(strcpy)
{
    char str1[] = "Sample string";
    char str2[40];
    char str3[40];

    strcpy(str2, str1);

    if (strcmp(str1, str2) != 0)
    {
        TEST_FAIL("strcpy1: failed to copy string.");
    }

    strcpy(str3, "copy successful");

    if (strcmp(str3, "copy successful") != 0)
    {
        TEST_FAIL("strcpy:2: failed to copy string.");
    }

    TEST_PASS;
}

TEST_IMPLEMENT(strncpy)
{
    char str1[] = "To be or not to be";
    char str2[40];
    char str3[40];

    strncpy(str2, str1, sizeof(str2));

    if (strcmp(str1, str2) != 0)
    {
        TEST_FAIL("strncpy:1: failed to copy string.");
    }

    strncpy(str3, str2, 5);
    str3[5] = '\0';

    if (strcmp(str3, "To be") != 0)
    {
        TEST_FAIL("strncpy:2: failed to copy string.");
    }

    TEST_PASS;
}

TEST_IMPLEMENT(strcat)
{
    char str[80];
    strcpy(str, "these ");
    strcat(str, "strings ");
    strcat(str, "are ");
    strcat(str, "concatenated.");

    if (strcmp(str, "these strings are concatenated.") != 0)
    {
        TEST_FAIL("strcat:1: failed to concatenate string.");
    }

    TEST_PASS;
}

TEST_IMPLEMENT(strncat)
{
    char str1[20];
    char str2[20];
    strcpy(str1, "To be ");
    strcpy(str2, "or not to be");
    strncat(str1, str2, 6);

    if (strcmp(str1, "To be or not") != 0)
    {
        TEST_FAIL("strncat:1: failed to concatenate string.");
    }

    TEST_PASS;
}

TEST_IMPLEMENT(memcmp)
{
    char buffer1[] = "DWgaOtP12df0";
    char buffer2[] = "DWGAOTP12DF0";
    int n;

    n = memcmp(buffer1, buffer2, sizeof(buffer1));

    if (n <= 0)
    {
        TEST_FAIL("memcmp:1: failed to compare greater memory.");
    }

    n = memcmp(buffer2, buffer1, sizeof(buffer1));

    if (n >= 0)
    {
        TEST_FAIL("memcmp:2: failed to compare lesser memory.");
    }

    n = memcmp(buffer1, buffer1, sizeof(buffer1));

    if (n != 0)
    {
        TEST_FAIL("memcmp:3: failed to compare equal memory.");
    }

    TEST_PASS;
}

TEST_IMPLEMENT(strcmp)
{
    char buffer1[] = "DWgaOtP12df0";
    char buffer2[] = "DWGAOTP12DF0";
    int n;

    n = strcmp(buffer1, buffer2);

    if (n <= 0)
    {
        TEST_FAIL("strcmp:1: failed to compare greater string.");
    }

    n = strcmp(buffer2, buffer1);

    if (n >= 0)
    {
        TEST_FAIL("strcmp:2: failed to compare lesser string.");
    }

    n = strcmp(buffer1, buffer1);

    if (n != 0)
    {
        TEST_FAIL("strcmp:3: failed to compare equal string.");
    }

    TEST_PASS;
}

BEGIN_TESTS(cstring)
{
    TEST(memcpy);
    TEST(memmove);
    TEST(strcpy);
    TEST(strncpy);
    TEST(strcat);
    TEST(strncat);
    TEST(memcmp);
    TEST(strcmp);
}
END_TESTS
