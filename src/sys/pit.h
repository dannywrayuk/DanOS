#pragma once
#include <stdint.h>

namespace sys
{
    void initPIT();
    uint64_t getTicks();
    void PITSetFreq(uint16_t f);

} // namespace sys