#include <stddef.h>
#include <common/cstring.h>

void *memcpy(void *destination, const void *source, size_t num)
{
    for (size_t i = 0; i < num; i++)
    {
        *((string)destination + i) = *((string)source + i);
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
                *((string)destination + i) = *((string)source + i);
            }
        }
        else
        {
            for (size_t i = num; i + 1 > 0; i--)
            {
                *((string)destination + i) = *((string)source + i);
            }
        }
    }
    return destination;
}

string strcpy(string destination, const string source)
{
    if (destination == NULL)
        return NULL;

    string ptr = destination;

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

string strcat(string destination, const string source)
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
    const string p1 = (const string)ptr1;
    const string p2 = (const string)ptr2;

    while (num-- > 0)
    {
        if (*p1++ != *p2++)
            return p1[-1] < p2[-1] ? -1 : 1;
    }
    return 0;
}

int strcmp(const string str1, const string str2)
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

int strcoll(const string str1, const string str2)
{
    return strcmp(str1, str2);
}

int strncmp(const string str1, const string str2, size_t num)
{
    for (int i = 0; i < num; i++)
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

size_t strxfrm(string destination, const string source, size_t num)
{
    strncpy(destination, source, num);
    return strlen(source);
}

const void *memchr(const void *ptr, int value, size_t num)
{
    unsigned string p = (unsigned string)ptr;
    while (num--)
        if (*p != (unsigned char)value)
            p++;
        else
            return p;
    return 0;
}

void *memchr(void *ptr, int value, size_t num)
{
    unsigned string p = (unsigned string)ptr;
    while (num--)
        if (*p != (unsigned char)value)
            p++;
        else
            return p;
    return 0;
}

const string strchr(const string str, int character)
{
    while (*str != (char)character)
        if (!*str++)
            return 0;
    return (string)str;
}

string strchr(string str, int character)
{
    while (*str != (char)character)
        if (!*str++)
            return 0;
    return (string)str;
}

size_t strcspn(const string str1, const string str2)
{
    size_t ret = 0;
    while (*str1)
        if (strchr(str2, *str1))
            return ret;
        else
            str1++, ret++;
    return ret;
}

const string strpbrk(const string str1, const string str2)
{
    while (*str1)
        if (strchr(str2, *str1++))
            return (string)--str1;
    return 0;
}

string strpbrk(string str1, const string str2)
{
    while (*str1)
        if (strchr(str2, *str1++))
            return (string)--str1;
    return 0;
}

const string strrchr(const string str, int character)
{
    string ret = 0;
    do
    {
        if (*str == (char)character)
            ret = (string)str;
    } while (*str++);
    return ret;
}

string strrchr(string str, int character)
{
    string ret = 0;
    do
    {
        if (*str == (char)character)
            ret = str;
    } while (*str++);
    return ret;
}

size_t strspn(const string str1, const string str2)
{
    size_t ret = 0;
    while (*str1 && strchr(str2, *str1++))
        ret++;
    return ret;
}

const string strstr(const string str1, const string str2)
{
    size_t n = strlen(str2);
    while (*str1)
        if (!memcmp(str1++, str2, n))
            return str1 - 1;
    return 0;
}

string strstr(string str1, const string str2)
{
    size_t n = strlen(str2);
    while (*str1)
        if (!memcmp(str1++, str2, n))
            return str1 - 1;
    return 0;
}

string strtok(string str, const string delimiters)
{
    string p = 0;
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
    unsigned string p = (unsigned string)ptr;
    while (num--)
        *p++ = (unsigned char)value;
    return p;
}

string strerror(int errnum)
{
    const string sys_errlist[] = {
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
    return (string)sys_errlist[errnum];
}

size_t strlen(const string str)
{
    size_t i;
    for (i = 0; str[i] != '\0'; i++)
        ;
    return i;
}