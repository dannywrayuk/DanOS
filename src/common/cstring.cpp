#include <stddef.h>
#include <common/cstring.h>

void *memcpy(void *destination, const void *source, size_t num)
{
    for (size_t i = 0; i < num; i++)
    {
        *((char *)destination + i) = *((char *)source + i);
    }
    return 0;
}

void *memmove(void *destination, const void *source, size_t num)
{
    if (destination != source)
    {
        if (destination < source)
        {
            for (size_t i = 0; i < num; i++)
            {
                *((char *)destination + i) = *((char *)source + i);
            }
        }
        else
        {
            for (size_t i = num; i + 1 > 0; i--)
            {
                *((char *)destination + i) = *((char *)source + i);
            }
        }
    }
    return destination;
}

string strcpy(string destination, const string source)
{
    if (destination == NULL)
        return NULL;

    char *ptr = destination;

    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = '\0';

    return ptr;
}

string strncpy(string destination, const string source, size_t num)
{
    if (destination == NULL)
        return NULL;

    size_t i;

    for (i = 0; i < num && source[i] != '\0'; i++)
        destination[i] = source[i];
    for (; i < num; i++)
        destination[i] = '\0';

    return destination;
}

char *strcat(char *destination, const char *source)
{
    int i, j;

    for (i = 0; destination[i] != '\0'; i++)
        ;

    for (j = 0; source[j] != '\0'; j++)
        destination[i + j] = source[j];

    destination[i + j] = '\0';

    return destination;
}

string strncat(string destination, const string source, size_t num)
{
    int i, j;

    for (i = 0; destination[i] != '\0'; i++)
        ;

    for (j = 0; source[j] != '\0' && j < num; j++)
        destination[i + j] = source[j];

    destination[i + j] = '\0';

    return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
    const char *p1 = (const char *)ptr1;
    const char *p2 = (const char *)ptr2;

    while (num-- > 0)
    {
        if (*p1++ != *p2++)
            return p1[-1] < p2[-1] ? -1 : 1;
    }
    return 0;
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
