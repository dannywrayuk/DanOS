#pragma once
#include <stdint.h>

uint8_t inb(uint16_t _port);

void outb(uint16_t _port, uint8_t _data);