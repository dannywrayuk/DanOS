#pragma once
#include <stddef.h>

#define COMPORT1 0x3f8

namespace io
{
    void initSerial();

    int isTransmitEmpty();

    void serialOut(char a);
    void serialOut(char *a);
    void serialOut(const char *a);
    void serialnOut(char *a, size_t num);

} // namespace io