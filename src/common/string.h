#pragma once
#include <stdint.h>

#define string const char *

int strlen(string str);
void reverse(char *s);
char *utoa(uint32_t n, uint8_t base);
char *itoa(int32_t n, uint8_t base);