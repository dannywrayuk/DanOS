#pragma once
#include <stddef.h>

#define string char *

// Copying

// Copy block of memory
// Copies the values of num bytes from the location pointed to by source directly to the memory block pointed to by destination.
void *memcpy(void *destination, const void *source, size_t num);

// Move block of memory
// Copies the values of num bytes from the location pointed by source to the memory block pointed by destination.
// Copying takes place as if an intermediate buffer were used, allowing the destination and source to overlap.
void *memmove(void *destination, const void *source, size_t num);

// Copy string
// Copies the C string pointed by source into the array pointed by destination, including the terminating null character (and stopping at that point).
string strcpy(string destination, const string source);

// Copy characters from string
// Copies the first num characters of source to destination.
// If the end of the source C string (which is signaled by a null-character) is found before num characters have been copied, destination is padded with zeros until a total of num characters have been written to it.
string strncpy(string destination, const string source, size_t num);

// Concatenation

// Concatenate strings
// Appends a copy of the source string to the destination string.
// The terminating null character in destination is overwritten by the first character of source, and a null-character is included at the end of the new string formed by the concatenation of both in destination.
string strcat(string destination, const string source);

// Append characters from string
// Appends the first num characters of source to destination, plus a terminating null-character.
string strncat(string destination, const string source, size_t num);

// Comparison

// Compare two blocks of memory
// Compares the first num bytes of the block of memory pointed by ptr1 to the first num bytes pointed by ptr2, returning zero if they all match or a value different from zero representing which is greater if they do not.
int memcmp(const void *ptr1, const void *ptr2, size_t num);

// Compare two strings
// Compares the C string str1 to the C string str2.
int strcmp(const char *str1, const char *str2);

// int strcoll(const char *str1, const char *str2);

// int strncmp(const string str1, const string str2, size_t num);

// size_t strxfrm(string destination, const string source, size_t num);

// Searching
// const void *memchr(const void *ptr, int value, size_t num);
// void *memchr(void *ptr, int value, size_t num);

// const string strchr(const string str, int character);
// string strchr(string str, int character);

// size_t strcspn(const string str1, const string str2);

// const string strpbrk(const string str1, const string str2);
// string strpbrk(string str1, const string str2);

// const string strrchr(const string str, int character);
// string strrchr(string str, int character);

// size_t strspn(const string str1, const string str2);

// const string strstr(const string str1, const string str2);
// string strstr(string str1, const string str2);

// string strtok(string str, const string delimiters);

// Other
// void *memset(void *ptr, int value, size_t num);

// string strerror(int errnum);

// size_t strlen(const string str);
