#include <common/std/stdlib.h>
#include <common/std/ctype.h>
#include <logging/debug.h>

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

static int maxExponent = 511;
static long double powersOf10[] = {10., 100., 1.0e4, 1.0e8, 1.0e16, 1.0e32, 1.0e64, 1.0e128, 1.0e256};

long double atold(const char *str)
{
    int sign, expSign = FALSE;
    long double fraction, dblExp, *d;
    register char *p, c;
    int exp = 0;
    int fracExp = 0;
    int mantSize;
    int decPt;
    char *pExp;

    p = (char *)str;
    while (isspace(*p))
    {
        p += 1;
    }
    if (*p == '-')
    {
        sign = TRUE;
        p += 1;
    }
    else
    {
        if (*p == '+')
        {
            p += 1;
        }
        sign = FALSE;
    }

    decPt = -1;
    for (mantSize = 0;; mantSize += 1)
    {
        c = *p;
        if (!isdigit(c))
        {
            if ((c != '.') || (decPt >= 0))
            {
                break;
            }
            decPt = mantSize;
        }
        p += 1;
    }

    pExp = p;
    p -= mantSize;
    if (decPt < 0)
    {
        decPt = mantSize;
    }
    else
    {
        mantSize -= 1;
    }
    if (mantSize > 18)
    {
        fracExp = decPt - 18;
        mantSize = 18;
    }
    else
    {
        fracExp = decPt - mantSize;
    }
    if (mantSize == 0)
    {
        return 0.0;
    }
    else
    {
        int frac1, frac2;
        frac1 = 0;
        for (; mantSize > 9; mantSize -= 1)
        {
            c = *p;
            p += 1;
            if (c == '.')
            {
                c = *p;
                p += 1;
            }
            frac1 = 10 * frac1 + (c - '0');
        }
        frac2 = 0;
        for (; mantSize > 0; mantSize -= 1)
        {
            c = *p;
            p += 1;
            if (c == '.')
            {
                c = *p;
                p += 1;
            }
            frac2 = 10 * frac2 + (c - '0');
        }
        fraction = (1.0e9 * frac1) + frac2;
    }

    p = pExp;
    if ((*p == 'E') || (*p == 'e'))
    {
        p += 1;
        if (*p == '-')
        {
            expSign = TRUE;
            p += 1;
        }
        else
        {
            if (*p == '+')
            {
                p += 1;
            }
            expSign = FALSE;
        }
        while (isdigit(*p))
        {
            exp = exp * 10 + (*p - '0');
            p += 1;
        }
    }
    if (expSign)
    {
        exp = fracExp - exp;
    }
    else
    {
        exp = fracExp + exp;
    }

    if (exp < 0)
    {
        expSign = TRUE;
        exp = -exp;
    }
    else
    {
        expSign = FALSE;
    }
    if (exp > maxExponent)
    {
        exp = maxExponent;
    }
    dblExp = 1.0;
    for (d = powersOf10; exp != 0; exp >>= 1, d += 1)
    {
        if (exp & 01)
        {
            dblExp *= *d;
        }
    }
    if (expSign)
    {
        fraction /= dblExp;
    }
    else
    {
        fraction *= dblExp;
    }

    if (sign)
    {
        return -fraction;
    }
    return fraction;
}

double atof(const char *str)
{
    return atold(str);
}

int atoi(const char *str)
{
    int res = 0;
    int i = 0;
    int sign = 1;
    for (; str[i] != '\0' && isspace(str[i]); ++i)
        ;
    if (str[i] == '-')
    {
        sign = -1;
        ++i;
    }
    for (; str[i] != '\0' && isdigit(str[i]); ++i)
    {
        res = res * 10 + str[i] - '0';
    }
    return sign * res;
}

long int atol(const char *str)
{
    long int res = 0;
    int i = 0;
    int sign = 1;
    for (; str[i] != '\0' && isspace(str[i]); ++i)
        ;
    if (str[i] == '-')
    {
        sign = -1;
        ++i;
    }
    for (; str[i] != '\0' && isdigit(str[i]); ++i)
    {
        res = res * 10 + str[i] - '0';
    }
    return sign * res;
}

long long int atoll(const char *str)
{
    long long int res = 0;
    int i = 0;
    int sign = 1;
    for (; str[i] != '\0' && isspace(str[i]); ++i)
        ;
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    for (; str[i] != '\0' && isdigit(str[i]); ++i)
    {
        res = res * 10 + str[i] - '0';
    }
    return sign * res;
}

double strtod(const char *str, char **endptr)
{
    return strtold(str, endptr);
}

float strtof(const char *str, char **endptr)
{
    return strtod(str, endptr);
}

long int strtol(const char *str, char **endptr, int base)
{
    return strtoll(str, endptr, base);
}

long double strtold(const char *str, char **endptr)
{
    char *p;
    if (endptr == (char **)0)
        return atold(str);

    p = (char *)str;

    while (isspace(*p))
        ++p;

    if (*p == '+' || *p == '-')
        ++p;
    /* INF or INFINITY.  */
    if ((p[0] == 'i' ||
         p[0] == 'I') &&
        (p[1] == 'n' ||
         p[1] == 'N') &&
        (p[2] == 'f' ||
         p[2] == 'F'))
    {
        if ((p[3] == 'i' ||
             p[3] == 'I') &&
            (p[4] == 'n' ||
             p[4] == 'N') &&
            (p[5] == 'i' ||
             p[5] == 'I') &&
            (p[6] == 't' ||
             p[6] == 'T') &&
            (p[7] == 'y' ||
             p[7] == 'Y'))
        {
            *endptr = p + 8;
            return atold(str);
        }
        else
        {
            *endptr = p + 3;
            return atold(str);
        }
    }
    /* NAN or NAN(foo).  */
    if ((p[0] == 'n' ||
         p[0] == 'N') &&
        (p[1] == 'a' ||
         p[1] == 'A') &&
        (p[2] == 'n' ||
         p[2] == 'N'))
    {
        p += 3;
        if (*p == '(')
        {
            ++p;
            while (*p != '\0' && *p != ')')
                ++p;
            if (*p == ')')
                ++p;
        }
        *endptr = p;
        return atold(str);
    }
    /* digits, with 0 or 1 periods in it.  */
    if (isdigit(*p) || *p == '.')
    {
        int got_dot = 0;
        while (isdigit(*p) || (!got_dot && *p == '.'))
        {
            if (*p == '.')
                got_dot = 1;
            ++p;
        }
        /* Exponent.  */
        if (*p == 'e' || *p == 'E')
        {
            int i;
            i = 1;
            if (p[i] == '+' || p[i] == '-')
                ++i;
            if (isdigit(p[i]))
            {
                while (isdigit(p[i]))
                    ++i;
                *endptr = p + i;
                return atold(str);
            }
        }
        *endptr = p;
        return atold(str);
    }
    /* Didn't find any digits.  Doesn't look like a number.  */
    *endptr = (char *)str;
    return 0.0;
}

long long int strtoll(const char *str, char **endptr, int base)
{
    if (base < 0 || base == 1 || base > 36)
        return 0;

    long long int res = 0;
    int i = 0;
    int sign = 1;
    for (; str[i] != '\0' && isspace(str[i]); i++)
        ;
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    if (base == 0)
    {
        base = 10;
        if (str[i] == '0')
        {
            base = 8;
            ++i;
            if (str[i] == 'x' || str[i] == 'X')
            {
                base = 16;
                ++i;
            }

            if (str[i] == 'b')
            {
                base = 2;
                ++i;
            }
        }
    }

    char offset = '0';
    for (; str[i] != '\0' && isalnum(str[i]); i++)
    {
        if (isdigit(str[i]))
            offset = '0';

        if (islower(str[i]))
            offset = 'a' - 10;

        if (isupper(str[i]))
            offset = 'A' - 10;

        if (str[i] - offset < base)
            res = res * base + str[i] - offset;
        else
            break;
    }
    if (endptr)
        *endptr = (char *)&str[i++];

    return sign * res;
}

unsigned long int strtoul(const char *str, char **endptr, int base)
{
    return strtoull(str, endptr, base);
}

unsigned long long int strtoull(const char *str, char **endptr, int base)
{
    if (base <= 0 || base == 1 || base > 36)
        return 0;

    unsigned long long int res = 0;
    int i = 0;
    int sign = 1;
    for (; str[i] != '\0' && isspace(str[i]); i++)
        ;
    if (str[i] == '-')
    {
        if (endptr)
            *endptr = (char *)&str[0];
        return 0;
    }
    if (base == 0)
    {
        base = 10;
        if (str[i] == '0')
        {
            base = 8;
            ++i;
            if (str[i] == 'x' || str[i] == 'X')
            {
                base = 16;
                ++i;
            }

            if (str[i] == 'b')
            {
                base = 2;
                ++i;
            }
        }
    }
    char offset = '0';
    for (; str[i] != '\0' && isalnum(str[i]); i++)
    {
        if (isdigit(str[i]))
            offset = '0';

        if (islower(str[i]))
            offset = 'a' - 10;

        if (isupper(str[i]))
            offset = 'A' - 10;

        if (str[i] - offset < base)
            res = res * base + str[i] - offset;
        else
            break;
    }
    if (endptr)
        *endptr = (char *)&str[i];

    return sign * res;
}