#include <limits.h>
#include <common/std/stdlib.h>
#include <common/std/ctype.h>
#include <logging/debug.h>
#include <stddef.h>

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

static int maxExponent = 511;
static long double powersOf10[] = {10., 100., 1.0e4, 1.0e8, 1.0e16, 1.0e32, 1.0e64, 1.0e128, 1.0e256};

namespace std
{

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

    static unsigned long int next = 1;

    int rand(void)
    {
        next = next * 1103515245 + 12345;
        return (unsigned int)(next / 65536) % UINT_MAX;
    }

    void srand(unsigned int seed)
    {
        next = seed;
    }

    void *bsearch(const void *key, const void *base, size_t num, size_t size, int (*compar)(const void *, const void *))
    {
        const char *pivot;
        int result;

        while (num > 0)
        {
            pivot = (char *)base + (num >> 1) * size;
            result = compar(key, pivot);

            if (result == 0)
                return (void *)pivot;

            if (result > 0)
            {
                base = pivot + size;
                num--;
            }
            num >>= 1;
        }

        return NULL;
    }

#define SWAP(a, b, size)             \
    do                               \
    {                                \
        size_t __size = (size);      \
        char *__a = (a), *__b = (b); \
        do                           \
        {                            \
            char __tmp = *__a;       \
            *__a++ = *__b;           \
            *__b++ = __tmp;          \
        } while (--__size > 0);      \
    } while (0)

#define MAX_THRESH 4

    typedef struct
    {
        char *lo;
        char *hi;
    } stack_node;

#define STACK_SIZE (CHAR_BIT * sizeof(size_t))
#define PUSH(low, high) ((void)((top->lo = (low)), (top->hi = (high)), ++top))
#define POP(low, high) ((void)(--top, (low = top->lo), (high = top->hi)))
#define STACK_NOT_EMPTY (stack < top)

    void qsort(void *base, size_t num, size_t size, int (*compar)(const void *, const void *))
    {
        char *base_ptr = (char *)base;
        const size_t max_thresh = MAX_THRESH * size;
        if (num == 0)
            return;
        if (num > MAX_THRESH)
        {
            char *lo = base_ptr;
            char *hi = &lo[size * (num - 1)];
            stack_node stack[STACK_SIZE];
            stack_node *top = stack;
            PUSH(NULL, NULL);
            while (STACK_NOT_EMPTY)
            {
                char *left_ptr;
                char *right_ptr;
                char *mid = lo + size * ((hi - lo) / size >> 1);
                if ((*compar)((void *)mid, (void *)lo) < 0)
                    SWAP(mid, lo, size);
                if ((*compar)((void *)hi, (void *)mid) < 0)
                    SWAP(mid, hi, size);
                else
                    goto jump_over;
                if ((*compar)((void *)mid, (void *)lo) < 0)
                    SWAP(mid, lo, size);
            jump_over:;
                left_ptr = lo + size;
                right_ptr = hi - size;
                do
                {
                    while ((*compar)((void *)left_ptr, (void *)mid) < 0)
                        left_ptr += size;
                    while ((*compar)((void *)mid, (void *)right_ptr) < 0)
                        right_ptr -= size;
                    if (left_ptr < right_ptr)
                    {
                        SWAP(left_ptr, right_ptr, size);
                        if (mid == left_ptr)
                            mid = right_ptr;
                        else if (mid == right_ptr)
                            mid = left_ptr;
                        left_ptr += size;
                        right_ptr -= size;
                    }
                    else if (left_ptr == right_ptr)
                    {
                        left_ptr += size;
                        right_ptr -= size;
                        break;
                    }
                } while (left_ptr <= right_ptr);
                if ((size_t)(right_ptr - lo) <= max_thresh)
                {
                    if ((size_t)(hi - left_ptr) <= max_thresh)
                        POP(lo, hi);
                    else
                        lo = left_ptr;
                }
                else if ((size_t)(hi - left_ptr) <= max_thresh)
                    hi = right_ptr;
                else if ((right_ptr - lo) > (hi - left_ptr))
                {
                    PUSH(lo, right_ptr);
                    lo = left_ptr;
                }
                else
                {
                    PUSH(left_ptr, hi);
                    hi = right_ptr;
                }
            }
        }
#define min(x, y) ((x) < (y) ? (x) : (y))
        {
            char *const end_ptr = &base_ptr[size * (num - 1)];
            char *tmp_ptr = base_ptr;
            char *thresh = min(end_ptr, base_ptr + max_thresh);
            char *run_ptr;
            for (run_ptr = tmp_ptr + size; run_ptr <= thresh; run_ptr += size)
                if ((*compar)((void *)run_ptr, (void *)tmp_ptr) < 0)
                    tmp_ptr = run_ptr;
            if (tmp_ptr != base_ptr)
                SWAP(tmp_ptr, base_ptr, size);
            run_ptr = base_ptr + size;
            while ((run_ptr += size) <= end_ptr)
            {
                tmp_ptr = run_ptr - size;
                while ((*compar)((void *)run_ptr, (void *)tmp_ptr) < 0)
                    tmp_ptr -= size;
                tmp_ptr += size;
                if (tmp_ptr != run_ptr)
                {
                    char *trav;
                    trav = run_ptr + size;
                    while (--trav >= run_ptr)
                    {
                        char c = *trav;
                        char *hi, *lo;
                        for (hi = lo = trav; (lo -= size) >= tmp_ptr; hi = lo)
                            *hi = *lo;
                        *hi = c;
                    }
                }
            }
        }
    }

    int abs(int n)
    {
        if (n < 0)
            n *= -1;
        return n;
    }
    long int abs(long int n)
    {
        if (n < 0)
            n *= -1;
        return n;
    }
    long long int abs(long long int n)
    {
        if (n < 0)
            n *= -1;
        return n;
    }

} // namespace std