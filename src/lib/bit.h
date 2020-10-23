#pragma once

#define testBit(base, offset) ({ \
    int ret;                     \
    asm volatile(                \
        "bt [%1], %2;"           \
        : "=@ccc"(ret)           \
        : "r"(base), "r"(offset) \
        : "memory");             \
    ret;                         \
})

#define setBit(base, offset) ({  \
    int ret;                     \
    asm volatile(                \
        "bts [%1], %2;"          \
        : "=@ccc"(ret)           \
        : "r"(base), "r"(offset) \
        : "memory");             \
    ret;                         \
})

#define resetBit(base, offset) ({ \
    int ret;                      \
    asm volatile(                 \
        "btr [%1], %2;"           \
        : "=@ccc"(ret)            \
        : "r"(base), "r"(offset)  \
        : "memory");              \
    ret;                          \
})
