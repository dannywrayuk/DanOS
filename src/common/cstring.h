#pragma once
#include <stddef.h>

#define string char *

void *memcpy(void *destination, const void *source, size_t num);

void *memmove(void *destination, const void *source, size_t num);

string strcpy(string destination, const string source);

string strncpy(string destination, const string source, size_t num);

string strcat(string destination, const string source);

string strncat(string destination, const string source, size_t num);

int memcmp(const void *ptr1, const void *ptr2, size_t num);

int strcmp(const char *str1, const char *str2);

int strcoll(const char *str1, const char *str2);

int strncmp(const string str1, const string str2, size_t num);

size_t strxfrm(string destination, const string source, size_t num);

const void *memchr(const void *ptr, int value, size_t num);
void *memchr(void *ptr, int value, size_t num);

const string strchr(const string str, int character);
string strchr(string str, int character);

size_t strcspn(const string str1, const string str2);

const string strpbrk(const string str1, const string str2);
string strpbrk(string str1, const string str2);

const string strrchr(const string str, int character);
string strrchr(string str, int character);

size_t strspn(const string str1, const string str2);

const string strstr(const string str1, const string str2);
string strstr(string str1, const string str2);

string strtok(string str, const string delimiters);

void *memset(void *ptr, int value, size_t num);

string strerror(int errnum);

size_t strlen(const string str);
