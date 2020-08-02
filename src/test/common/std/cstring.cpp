#include <test/test.h>
#include <common/std/cstring.h>
#include <logging/debug.h>

BEGIN_IMPLEMENT(memcpy)
{
    struct
    {
        char property1[16];
        int property2;
    } object, object_copy;

    char property3[16] = "dannywray.co.uk";

    std::memcpy(object.property1, property3, 16);

    if (std::strcmp(object.property1, property3) != 0)
    {
        TEST_FAIL("1: failed to copy string.");
    }

    object.property2 = 69;
    std::memcpy(&object_copy, &object, sizeof(object));

    if (object.property2 != object_copy.property2 && std::strcmp(object_copy.property1, property3) != 0)
    {
        TEST_FAIL("2: failed to copy structure.");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(memmove)
{
    char str[] = "memmove can be very useful......";
    char result[] = "memmove can be very very useful.";

    std::memmove(str + 20, str + 15, 11);
    if (std::strcmp(str, result) != 0)
    {
        TEST_FAIL("1: failed to move string.");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strcpy)
{
    char str1[] = "Sample string";
    char str2[40];
    char str3[40];

    std::strcpy(str2, str1);

    if (std::strcmp(str1, str2) != 0)
    {
        TEST_FAIL("1: failed to copy string.");
    }

    std::strcpy(str3, "copy successful");

    if (std::strcmp(str3, "copy successful") != 0)
    {
        TEST_FAIL("2: failed to copy string.");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strncpy)
{
    char str1[] = "To be or not to be";
    char str2[40];
    char str3[40];

    std::strncpy(str2, str1, sizeof(str2));

    if (std::strcmp(str1, str2) != 0)
    {
        TEST_FAIL("1: failed to copy string.");
    }

    std::strncpy(str3, str2, 5);
    str3[5] = '\0';

    if (std::strcmp(str3, "To be") != 0)
    {
        TEST_FAIL("2: failed to copy string.");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strcat)
{
    char str[80];
    std::strcpy(str, "these ");
    std::strcat(str, "strings ");
    std::strcat(str, "are ");
    std::strcat(str, "concatenated.");

    if (std::strcmp(str, "these strings are concatenated.") != 0)
    {
        TEST_FAIL("1: failed to concatenate string.");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strncat)
{
    char str1[20];
    char str2[20];
    std::strcpy(str1, "To be ");
    std::strcpy(str2, "or not to be");
    std::strncat(str1, str2, 6);

    if (std::strcmp(str1, "To be or not") != 0)
    {
        TEST_FAIL("1: failed to concatenate string.");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(memcmp)
{
    char buffer1[] = "DWgaOtP12df0";
    char buffer2[] = "DWGAOTP12DF0";
    int n;

    n = std::memcmp(buffer1, buffer2, sizeof(buffer1));

    if (n <= 0)
    {
        TEST_FAIL("1: failed to compare greater memory.");
    }

    n = std::memcmp(buffer2, buffer1, sizeof(buffer1));

    if (n >= 0)
    {
        TEST_FAIL("2: failed to compare lesser memory.");
    }

    n = std::memcmp(buffer1, buffer1, sizeof(buffer1));

    if (n != 0)
    {
        TEST_FAIL("3: failed to compare equal memory.");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strcmp)
{
    char buffer1[] = "DWgaOtP12df0";
    char buffer2[] = "DWGAOTP12DF0";
    int n;

    n = std::strcmp(buffer1, buffer2);

    if (n <= 0)
    {
        TEST_FAIL("1: failed to compare greater string.");
    }

    n = std::strcmp(buffer2, buffer1);

    if (n >= 0)
    {
        TEST_FAIL("2: failed to compare lesser string.");
    }

    n = std::strcmp(buffer1, buffer1);

    if (n != 0)
    {
        TEST_FAIL("3: failed to compare equal string.");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strcoll)
{
    char buffer1[] = "DWgaOtP12df0";
    char buffer2[] = "DWGAOTP12DF0";
    int n;

    n = std::strcoll(buffer1, buffer2);

    if (n <= 0)
    {
        TEST_FAIL("1: failed to compare greater string.");
    }

    n = std::strcoll(buffer2, buffer1);

    if (n >= 0)
    {
        TEST_FAIL("2: failed to compare lesser string.");
    }

    n = std::strcoll(buffer1, buffer1);

    if (n != 0)
    {
        TEST_FAIL("3: failed to compare equal string.");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strncmp)
{
    char str[][5] = {"R2D2", "C3PO", "R2A6"};

    if (std::strncmp(str[0], "R2xx", 2) != 0)
    {
        TEST_FAIL("1: didn't match string");
    }

    if (std::strncmp(str[1], "R2xx", 2) == 0)
    {
        TEST_FAIL("2: matched incorrect string");
    }

    if (std::strncmp(str[2], "R2xx", 2) != 0)
    {
        TEST_FAIL("3: didn't match string");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strxfrm)
{
    char src[15], dest[15];
    int len;
    std::strcpy(src, "hellothere");
    len = std::strxfrm(dest, src, 11);

    if (len != 10)
    {
        TEST_FAIL("1: length is incorrect");
    }

    if (std::strcmp(dest, "hellothere") != 0)
    {
        TEST_FAIL("2: didn't copy string");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(memchr)
{
    const char *s1 = "";
    const char *s2 = "abcdefabcdef";
    const char *s3 = "11111111111111111111";

    if (std::memchr(s1, 'x', 0) != NULL)
    {
        TEST_FAIL("1: found absent char");
    }

    if (std::memchr(s2, 'y', 0) != NULL)
    {
        TEST_FAIL("2: found absent char");
    }

    if ((char *)std::memchr(s2, 'a', 1) - s2 != 0)
    {
        TEST_FAIL("3: found absent char");
    }

    if (std::memchr(s2, 'd', 2) != NULL)
    {
        TEST_FAIL("4: found absent char");
    }

    if ((char *)std::memchr(s2, 'd', 12) - s2 != 3)
    {
        TEST_FAIL("5: didn't find char");
    }

    if ((char *)std::memchr(s2, 'f', 12) - s2 != 5)
    {
        TEST_FAIL("6: didn't find char");
    }

    if ((char *)std::memchr(s3, '1', 20) - s3 != 0)
    {
        TEST_FAIL("7: found absent char");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strchr)
{
    char str[] = "This is a sample string";
    int locations[4] = {4, 7, 11, 18};
    char *pch;
    pch = std::strchr(str, 's');
    for (int i = 0; pch != NULL; i++)
    {
        if ((int)(pch - str + 1) != locations[i])
        {
            TEST_FAIL("1: incorrect char location");
        }
        pch = std::strchr(pch + 1, 's');
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strcspn)
{
    char str[] = "fcba73";
    char keys[] = "1234567890";
    if (std::strcspn(str, keys) != 4)
    {
        TEST_FAIL("1: span incorrect length");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strpbrk)
{
    char str[] = "This is a sample string";
    char key[] = "aeiou";
    const char *vowels = "iiaaei";
    char *pch;
    pch = std::strpbrk(str, key);
    for (int i = 0; pch != NULL; i++)
    {
        if (*pch != vowels[i])
        {
            TEST_FAIL("1: incorrect char location");
        }
        pch = std::strpbrk(pch + 1, key);
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strrchr)
{
    char str[] = "This is a sample string";

    if ((int)(std::strrchr(str, 's') - str + 1) != 18)
    {
        TEST_FAIL("1: incorrect char location");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strspn)
{
    char strtext[] = "129th";
    char cset[] = "1234567890";
    if (std::strspn(strtext, cset) != 3)
    {
        TEST_FAIL("1: incorrect span length");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strstr)
{
    char str[] = "This is a simple string";
    if ((int)(std::strstr(str, "simple") - str + 1) != 11)
    {
        TEST_FAIL("1: incorrect start location");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strtok)
{
    char str[] = "- This, a sample string.";
    char *pch;
    const char *tokens[] = {"This", "a", "sample", "string"};
    pch = std::strtok(str, " ,.-");
    for (int i = 0; pch != NULL; i++)
    {
        if (std::strcmp(pch, tokens[i]) != 0)
        {
            TEST_FAIL("1: didn't match token");
        }
        pch = std::strtok(NULL, " ,.-");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(memset)
{
    char str[] = "almost every programmer should know memset!";
    std::memset(str, '-', 6);
    if (std::strcmp(str, "------ every programmer should know memset!") != 0)
    {
        TEST_FAIL("1: memory was set incorrectly");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strerror)
{
    // Not required
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strlen)
{
    char str1[] = "almost every programmer should know memset!";
    char str2[] = "";

    if (std::strlen(str1) != 43)
    {
        TEST_FAIL("1: incorrect length");
    }

    if (std::strlen(str2) != 0)
    {
        TEST_FAIL("1: incorrect length empty string");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strrev)
{
    char string[23] = "hello this is a string";
    char result[23] = "gnirts a si siht olleh";
    std::strrev(string);
    if (std::strcmp(result, string))
    {
        TEST_FAIL("1: failed to reverse string");
    }
}
END_IMPLEMENT

BEGIN_IMPLEMENT(strnrev)
{
    char string[23] = "hello this is a string";
    char result[23] = "olleh this is a string";
    std::strnrev(string, 5);
    if (std::strcmp(string, result))
    {
        TEST_FAIL("1: failed to reverse part of string");
    }
}
END_IMPLEMENT

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
    TEST(strcoll)
    TEST(strncmp);
    TEST(strxfrm);
    TEST(memchr);
    TEST(strchr);
    TEST(strcspn);
    TEST(strpbrk);
    TEST(strrchr);
    TEST(strspn);
    TEST(strstr);
    TEST(strtok);
    TEST(memset);
    TEST(strerror);
    TEST(strlen);
    TEST(strrev);
    TEST(strnrev);
}
END_TESTS
