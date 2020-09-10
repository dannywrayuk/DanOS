#pragma once
#include <stddef.h>
#include <stdint.h>

namespace std
{
    // Write formatted data to string
    // Composes a string with the same text that would be printed if format was used on printf, but instead of being printed, the content is stored as a C string in the buffer pointed by str.
    uint32_t sprintf(char *str, const char *format, ...);

    // Write formatted output to sized buffer
    // Composes a string with the same text that would be printed if format was used on printf, but instead of being printed, the content is stored as a C string in the buffer pointed by s (taking n as the maximum buffer capacity to fill).
    uint32_t snprintf(char *str, size_t n, const char *format, ...);

    // Print formatted data to stdout
    // Writes the C string pointed by format to the standard output (stdout). If format includes format specifiers (subsequences beginning with %), the additional arguments following format are formatted and inserted in the resulting string replacing their respective specifiers.
    uint32_t printf(const char *format, ...);

} // namespace std