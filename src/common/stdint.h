#pragma once

typedef unsigned char uint8_t;
typedef signed char int8_t;

typedef unsigned short uint16_t;
typedef signed short int16_t;

typedef unsigned int uint32_t;
typedef signed int int32_t;

typedef unsigned long long uint64_t;
typedef signed long long int64_t;

typedef const char *string_t;

// Allow Packed Structures without Intellisense Errors
#ifdef __INTELLISENSE__
#define packed
#define __attribute__()
#endif

#define ASM(x) __asm __volatile__(x)