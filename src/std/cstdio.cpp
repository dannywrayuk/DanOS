#include <stdarg.h>
#include <std/cstdio.h>
#include <std/cstring.h>
#include <std/cstdlib.h>
#include <io/serial.h>

namespace std
{

    void _sprintf_switch(char *buffer, char **str, va_list *argpp)
    {
        uint8_t prefix = 0;
        uint8_t dplace = 6;
        if (*(*str + 1) == '#')
        {
            ++*str;
            prefix = 1;
        }
        if (*(*str + 1) == '.')
        {
            *str += 2;
            dplace = **str - '0';
        }
        char c[2] = "\0";
        switch (*(++*str))
        {
        // Percentage
        case '%':
            std::strcpy(buffer, "%");
            break;

        // Signed decimal int
        case 'd':
        case 'i':
            std::itoa(va_arg(*argpp, int32_t), buffer, 10, prefix);
            break;

        // Unsigned binary int
        case 'b':
            std::utoa(va_arg(*argpp, uint32_t), buffer, 2, prefix);
            break;

        // Unsigned decimal int
        case 'u':
            std::utoa(va_arg(*argpp, uint32_t), buffer, 10, prefix);
            break;

        // Unsigned octal int
        case 'o':
            std::utoa(va_arg(*argpp, uint32_t), buffer, 8, prefix);
            break;

        // Unsigned hex int
        case 'x':
        case 'X':
            std::utoa(va_arg(*argpp, uint32_t), buffer, 16, prefix);
            break;

        // Decimal float
        case 'f':
        case 'F':
            std::ftoa(va_arg(*argpp, double), buffer, dplace);
            break;

        // Character
        case 'c':
            c[0] = va_arg(*argpp, int32_t);
            std::strcpy(buffer, c);
            break;

        // String
        case 's':
            std::strcpy(buffer, va_arg(*argpp, char *));
            break;

        default:
            break;
        }
    }

    uint32_t _snprintf_internal(char *str, size_t n, const char *format, va_list *argpp)
    {
        char *occ1 = (char *)format;
        char *occ2 = std::strchr(occ1, '%');
        std::strncat(str, occ1, occ2 - occ1);
        char buffer[100];

        size_t space = (n == -1) ? -1 : n - std::strlen(str) - 1;

        while (occ2 != NULL && space > 0)
        {

            _sprintf_switch(buffer, &occ2, argpp);
            std::strncat(str, buffer, space);
            occ1 = ++occ2;
            occ2 = std::strchr(occ1, '%');
            if (n == -1)
            {
                std::strncat(str, occ1, occ2 - occ1);
            }
            else
            {
                if (space > occ2 - occ1)
                {
                    space = occ2 - occ1;
                }
                std::strncat(str, occ1, space);
                space = n - std::strlen(str) - 1;
            }
        }
        std::strcat(str, "");
        return 0;
    }

    uint32_t sprintf(char *str, const char *format, ...)
    {
        va_list argp;
        va_start(argp, format);
        uint32_t ret = _snprintf_internal(str, -1, format, &argp);
        va_end(argp);
        return ret;
    }

    uint32_t snprintf(char *str, size_t n, const char *format, ...)
    {
        va_list argp;
        va_start(argp, format);
        uint32_t ret = _snprintf_internal(str, n, format, &argp);
        va_end(argp);
        return ret;
    }

    uint32_t printf(const char *format, ...)
    {
        va_list argp;
        va_start(argp, format);

        char *occ1 = (char *)format;
        char *occ2 = std::strchr(occ1, '%');

        io::serialnOut(occ1, occ2 - occ1);

        char buffer[500];

        while (occ2 != NULL)
        {
            _sprintf_switch(buffer, &occ2, &argp);
            io::serialOut(buffer);
            occ1 = ++occ2;
            occ2 = std::strchr(occ1, '%');
            io::serialnOut(occ1, occ2 - occ1);
        }
        io::serialOut("");
        va_end(argp);
        return 0;
    }

} // namespace std