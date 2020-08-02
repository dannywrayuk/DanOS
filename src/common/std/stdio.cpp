#include <stdarg.h>
#include <common/std/stdio.h>
#include <common/std/cstring.h>
#include <common/std/stdlib.h>

namespace std
{
    int sprintf(char *str, const char *format, ...)
    {
        va_list argp;
        va_start(argp, format);

        char *occ1 = (char *)format;
        char *occ2 = std::strchr(occ1, '%');
        std::strncat(str, occ1, occ2 - occ1);
        char buffer[100];
        while (occ2 != NULL)
        {
            int prefix = 0;
            if (*(occ2 + 1) == '#')
            {
                ++occ2;
                prefix = 1;
            }
            switch (*(++occ2))
            {
            // Percentage
            case '%':
                std::strcat(str, "%");
                break;

            // Signed decimal int
            case 'd':
            case 'i':
                std::itoa(va_arg(argp, int), buffer, 10, prefix);
                std::strcat(str, buffer);
                break;

            // Unsigned binary int
            case 'b':
                std::utoa(va_arg(argp, int), buffer, 2, prefix);
                std::strcat(str, buffer);
                break;

            // Unsigned decimal int
            case 'u':
                std::utoa(va_arg(argp, int), buffer, 10, prefix);
                std::strcat(str, buffer);
                break;

            // Unsigned octal int
            case 'o':
                std::utoa(va_arg(argp, int), buffer, 8, prefix);
                std::strcat(str, buffer);
                break;

            // Unsigned hex int
            case 'x':
            case 'X':
                std::utoa(va_arg(argp, int), buffer, 16, prefix);
                std::strcat(str, buffer);
                break;

            // // Decimal float
            // case 'f':
            //     std::ftoa(va_arg(argp, int), buffer, 3);
            //     std::strcat(str, buffer);
            //     break;

            // Character
            case 'c':
                buffer[0] = va_arg(argp, int);
                buffer[1] = '\0';
                std::strcat(str, buffer);
                break;

            // String
            case 's':
                std::strcat(str, va_arg(argp, char *));
                break;

            default:
                break;
            }
            occ1 = ++occ2;
            occ2 = std::strchr(occ1, '%');
            std::strncat(str, occ1, occ2 - occ1);
        }
        std::strcat(str, "");
        return 0;
    }
} // namespace std