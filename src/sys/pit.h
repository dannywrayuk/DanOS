#pragma once
#include <stdint.h>

namespace sys
{
    namespace pit
    {
        uint64_t getTicks();
        void PITSetFreq(uint16_t f);

        void initPIT();

    } // namespace pit

} // namespace sys