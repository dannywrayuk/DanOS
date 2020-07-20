#include <stdint.h>
#include <common/string.h>

// Base Charset
string BASE_CHARSET = "0123456789ABCDEF";

//Integer to String conversion
int strlen(string str)
{
    uint32_t i = 0;
    uint32_t maxlen = 0xffffffff;
    while (str[i] != '\0' && i < maxlen)
    {
        i++;
    }
    return i;
}

void reverse(char *s)
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

char *utoa(uint32_t n, uint8_t base)
{
    if (base > 16 || base < 2)
    {
        base = 10;
    }
    char *out;

    uint8_t i = 0;
    while (n > 0)
    {
        out[i] = BASE_CHARSET[n % base];
        n /= base;
        i++;
    }
    if (base == 2)
    {
        out[i] = 'b';
        i++;
        out[i] = '0';
        i++;
    }
    if (base == 8)
    {
        out[i] = '0';
        i++;
    }
    if (base == 16)
    {
        out[i] = 'x';
        i++;
        out[i] = '0';
        i++;
    }
    out[i] = '\0';
    reverse(out);

    return out;
}

char *itoa(int32_t n, uint8_t base)
{
    int8_t sign = 1;
    if (n < 0)
    {
        sign = -1;
        n = n * sign;
    }
    if (base > 16 || base < 2)
    {
        base = 10;
    }
    char *out;

    uint8_t i = 0;
    while (n > 0)
    {
        out[i] = BASE_CHARSET[n % base];
        n /= base;
        i++;
    }
    if (base == 2)
    {
        out[i] = 'b';
        i++;
        out[i] = '0';
        i++;
    }
    if (base == 8)
    {
        out[i] = '0';
        i++;
    }
    if (base == 16)
    {
        out[i] = 'x';
        i++;
        out[i] = '0';
        i++;
    }
    if (sign < 0)
    {
        out[i] = '-';
        i++;
    }
    out[i] = '\0';
    reverse(out);

    return out;
}