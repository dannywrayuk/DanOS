#include <std/cmath.h>

namespace std
{
    int32_t pow(int32_t x, uint32_t y)
    {
        if (y == 0)
            return 1;
        else if (y % 2 == 0)
            return pow(x, y / 2) * pow(x, y / 2);
        else
            return x * pow(x, y / 2) * pow(x, y / 2);
    }
} // namespace std