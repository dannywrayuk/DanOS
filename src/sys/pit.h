#pragma once
#include <stdint.h>

namespace pit
{
    uint64_t getTicks();
    void PITSetFreq(uint16_t f);

    void initPIT();

} // namespace pit
