#pragma once

namespace std
{
    // Write formatted data to string
    // Composes a string with the same text that would be printed if format was used on printf, but instead of being printed, the content is stored as a C string in the buffer pointed by str.
    int sprintf(char *str, const char *format, ...);

} // namespace std