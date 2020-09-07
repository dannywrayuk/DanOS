#pragma once
#include <stddef.h>

// The GNU C Compiler in freestanding mode requires the existence of the symbols.

// Copy block of memory
// Copies the values of num bytes from the location pointed to by source directly to the memory block pointed to by destination.
extern "C" void *memcpy(void *destination, const void *source, size_t num);

// Move block of memory
// Copies the values of num bytes from the location pointed by source to the memory block pointed by destination.
// Copying takes place as if an intermediate buffer were used, allowing the destination and source to overlap.
extern "C" void *memmove(void *destination, const void *source, size_t num);

// Compare two blocks of memory
// Compares the first num bytes of the block of memory pointed by ptr1 to the first num bytes pointed by ptr2, returning zero if they all match or a value different from zero representing which is greater if they do not.
extern "C" int memcmp(const void *ptr1, const void *ptr2, size_t num);

// Fill block of memory
// Sets the first num bytes of the block of memory pointed by ptr to the specified value (interpreted as an unsigned char).
extern "C" void *memset(void *ptr, int value, size_t num);