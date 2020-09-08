#include <stddef.h>
#include <std/cstring.h>

namespace std
{

    void *memcpy(void *destination, const void *source, size_t num)
    {
        char *dp = (char *)destination;
        const char *sp = (const char *)source;
        while (num--)
            *dp++ = *sp++;
        return destination;
    }

    void *memmove(void *destination, const void *source, size_t num)
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

    char *strcpy(char *destination, const char *source)
    {
        char *ret = destination;
        while (*destination++ = *source++)
            ;
        return ret;
    }

    char *strncpy(char *destination, const char *source, size_t num)
    {
        char *ret = destination;
        do
        {
            if (!num--)
                return ret;
        } while (*destination++ = *source++);
        while (num--)
            *destination++ = 0;
        return ret;
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

    char *strncat(char *destination, const char *source, size_t num)
    {
        int i, j;

        for (i = 0; destination[i] != '\0'; i++)
            ;

        for (j = 0; source[j] != '\0' && j < num; j++)
            destination[i + j] = source[j];

        destination[i + j] = '\0';

        return destination;
    }

    int32_t memcmp(const void *ptr1, const void *ptr2, size_t num)
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

    int32_t strcmp(const char *str1, const char *str2)
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

    int32_t strcoll(const char *str1, const char *str2)
    {
        return strcmp(str1, str2);
    }

    int32_t strncmp(const char *str1, const char *str2, size_t num)
    {
        for (uint32_t i = 0; i < num; i++)
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
        return 0;
    }

    size_t strxfrm(char *destination, const char *source, size_t num)
    {
        strncpy(destination, source, num);
        return strlen(source);
    }

    const void *memchr(const void *ptr, int value, size_t num)
    {
        unsigned char *p = (unsigned char *)ptr;
        while (num--)
            if (*p != (unsigned char)value)
                p++;
            else
                return p;
        return 0;
    }

    void *memchr(void *ptr, int value, size_t num)
    {
        unsigned char *p = (unsigned char *)ptr;
        while (num--)
            if (*p != (unsigned char)value)
                p++;
            else
                return p;
        return 0;
    }

    const char *strchr(const char *str, int character)
    {
        while (*str != (char)character)
            if (!*str++)
                return 0;
        return (char *)str;
    }

    char *strchr(char *str, int character)
    {
        while (*str != (char)character)
            if (!*str++)
                return 0;
        return (char *)str;
    }

    size_t strcspn(const char *str1, const char *str2)
    {
        size_t ret = 0;
        while (*str1)
            if (strchr(str2, *str1))
                return ret;
            else
                str1++, ret++;
        return ret;
    }

    const char *strpbrk(const char *str1, const char *str2)
    {
        while (*str1)
            if (strchr(str2, *str1++))
                return (char *)--str1;
        return 0;
    }

    char *strpbrk(char *str1, const char *str2)
    {
        while (*str1)
            if (strchr(str2, *str1++))
                return (char *)--str1;
        return 0;
    }

    const char *strrchr(const char *str, int character)
    {
        char *ret = 0;
        do
        {
            if (*str == (char)character)
                ret = (char *)str;
        } while (*str++);
        return ret;
    }

    char *strrchr(char *str, int character)
    {
        char *ret = 0;
        do
        {
            if (*str == (char)character)
                ret = str;
        } while (*str++);
        return ret;
    }

    size_t strspn(const char *str1, const char *str2)
    {
        size_t ret = 0;
        while (*str1 && strchr(str2, *str1++))
            ret++;
        return ret;
    }

    const char *strstr(const char *str1, const char *str2)
    {
        size_t n = strlen(str2);
        while (*str1)
            if (!memcmp(str1++, str2, n))
                return str1 - 1;
        return 0;
    }

    char *strstr(char *str1, const char *str2)
    {
        size_t n = strlen(str2);
        while (*str1)
            if (!memcmp(str1++, str2, n))
                return str1 - 1;
        return 0;
    }

    char *strtok(char *str, const char *delimiters)
    {
        char *p = 0;
        if (str)
            p = str;
        else if (!p)
            return 0;
        str = p + strspn(p, delimiters);
        p = str + strcspn(str, delimiters);
        if (p == str)
            return p = 0;
        p = *p ? *p = 0, p + 1 : 0;
        return str;
    }

    void *memset(void *ptr, int value, size_t num)
    {
        unsigned char *p = (unsigned char *)ptr;
        while (num--)
            *p++ = (unsigned char)value;
        return p;
    }

    char *strerror(uint8_t errnum)
    {
        const char *sys_errlist[] = {
            "Operation succeeded",
            "Invalid argument",
            "Bad memory address",
            "String too long",
            "Out of memory",
            "Input/output error",
            "No such file or directory",
            "Not a directory",
            "Is a directory",
            "File or object exists",
            "Cross-device link",
            "Try again later",
            "Illegal seek",
            "Unimplemented feature",
            "Device not available",
            "No such device",
            "Device or resource busy",
            "Invalid/inappropriate ioctl",
            "Directory not empty",
            "Result too large",
            "No space left on device",
            "Too many open files",
            "Too many open files in system"
            "No such system call",
            "File is not executable",
            "Argument list too long",
            "Bad file number",
        };
        return (char *)sys_errlist[errnum];
    }

    size_t strlen(const char *str)
    {
        size_t i;
        for (i = 0; str[i] != '\0'; i++)
            ;
        return i;
    }

    char *strnrev(char *str, size_t num)
    {
        int32_t i, j;
        char c;
        for (i = 0, j = num - 1; i < j; i++, j--)
        {
            c = str[i];
            str[i] = str[j];
            str[j] = c;
        }
        return str;
    }

    char *strrev(char *str)
    {
        int32_t i, j;
        char c;
        for (i = 0, j = strlen(str) - 1; i < j; i++, j--)
        {
            c = str[i];
            str[i] = str[j];
            str[j] = c;
        }
        return str;
    }
} // namespace std