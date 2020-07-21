#include <stddef.h>
#include <common/cstring.h>

void *memcpy(void *destination, const void *source, size_t num)
{
    char *c_destination = (char *)destination;
    char *c_source = (char *)source;
    for (size_t i = 0; i < num; i++)
    {
        c_destination[i] = c_source[i];
    }
    return 0;
}

//
void *memmove(void *destination, const void *source, size_t num)
{
    signed char operation;
    size_t end;
    size_t current;

    if (destination != source)
    {
        if (destination < source)
        {
            operation = 1;
            current = 0;
            end = num;
        }
        else
        {
            operation = -1;
            current = num - 1;
            end = -1;
        }

        for (; current != end; current += operation)
        {
            *(((unsigned char *)destination) + current) = *(((unsigned char *)source) + current);
        }
    }
    return destination;
}

int strcmp(const char *str1, const char *str2)
{
    for (int i = 0;; i++)
    {
        if (str1[i] != str2[i])
        {
            return str1[i] < str2[i] ? -1 : 1;
        }

        if (str1[i] == '\0')
        {
            return 0;
        }
    }
}
