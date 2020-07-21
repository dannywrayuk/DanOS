#pragma once
#include <common/cstring.h>
#include <stdint.h>

void dbg(const string msg);
void dbg(string msg);
void dbg_label(const string msg, const string col);
void dbgc(char msg);
// void dbg(uint32_t msg);
void endl();
