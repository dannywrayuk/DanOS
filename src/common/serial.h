#pragma once
#include <common/cstring.h>

#define COMPORT1 0x3f8

void init_serial();

int is_transmit_empty();

void write_serial(char a);
void write_serial(string a);
void write_serial(const string a);

int serial_received();