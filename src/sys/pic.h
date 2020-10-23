#pragma once
#include <stdint.h>

namespace pic
{
    void EOI(uint8_t vec);
    void remap(uint8_t pic0_offset, uint8_t pic1_offset);
    void setMask(uint8_t line, int status);
    void maskAll();

    void init();

} // namespace pic
