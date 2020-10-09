#pragma once
#include <stdint.h>

namespace sys
{

    void picEOI(uint8_t vec);
    void picRemap(uint8_t pic0_offset, uint8_t pic1_offset);
    void picSetMask(uint8_t line, int status);
    void picMaskAll();

    void initPIC();

} // namespace sys