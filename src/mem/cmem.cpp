#include <mem/cmem.h>
#include <io/serial.h>

extern "C" void *memcpy(void *destination, const void *source, size_t num)
{
    char *dp = (char *)destination;
    const char *sp = (const char *)source;
    while (num--)
        *dp++ = *sp++;
    return destination;
}

extern "C" void *memmove(void *destination, const void *source, size_t num)
{
    unsigned char *pd = (unsigned char *)destination;
    const unsigned char *ps = (const unsigned char *)source;
    if (ps < pd)
        for (pd += num, ps += num; num--;)
            *--pd = *--ps;
    else
        while (num--)
            *pd++ = *ps++;
    return destination;
}

extern "C" int memcmp(const void *ptr1, const void *ptr2, size_t num)
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

extern "C" void *memset(void *ptr, uint32_t value, size_t num)
{
    unsigned char *p = (unsigned char *)ptr;
    while (num--)
        *p++ = (unsigned char)value;
    return p;
}