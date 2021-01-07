#pragma once
#include <stddef.h>
#include <mem/slab.h>

void *malloc(size_t size);
void *calloc(size_t size);
void *realloc(void *ptr, size_t size);
void* recalloc(void* ptr, size_t size);
void free(void *ptr);
