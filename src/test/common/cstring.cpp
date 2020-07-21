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

    /* copy string: */
    memcpy(object.property1, property3, 16);

    if (strcmp(object.property1, property3) != 0)
    {
        TEST_FAIL("memcpy: failed to copy string.");
    }

    object.property2 = 69;
    /* copy structure: */
    memcpy(&object_copy, &object, sizeof(object));

    if (object.property2 != object_copy.property2 && strcmp(object_copy.property1, property3) != 0)
    {
        TEST_FAIL("memcpy: failed to copy structure.");
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
        TEST_FAIL("memmove: failed to move string.");
    }
    TEST_PASS;
}

TEST_IMPLEMENT(strcpy)
{

    // TEST_FAIL("memmove: failed to move string.");
    TEST_PASS;
}

BEGIN_TESTS(cstring)
{
    TEST(memcpy);
    TEST(memmove);
    TEST(strcpy);
}
END_TESTS
