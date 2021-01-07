#pragma once
#include <stddef.h>

namespace serial
{
    int isTransmitEmpty();

    void out(char a);
    void out(char *a);
    void out(const char *a);
    void outN(char *a, size_t num);

    void init();

} // namespace serial
