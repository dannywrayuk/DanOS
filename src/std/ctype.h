#pragma once
#include <stdint.h>

// Character handling functions
// This header declares a set of functions to classify and transform individual characters.

// Character classification functions

// Check if character is alphanumeric
uint8_t isalnum(char c);

// Check if character is alphabetic
uint8_t isalpha(char c);

// Check if character is blank
uint8_t isblank(char c);

// Check if character is a control character
uint8_t iscntrl(char c);

// Check if character is decimal digit
uint8_t isdigit(char c);

// Check if character has graphical representation
uint8_t isgraph(char c);

// Check if character is lowercase letter
uint8_t islower(char c);

// Check if character is printable
uint8_t isprint(char c);

// Check if character is a punctuation character
uint8_t ispunct(char c);

// Check if character is a white-space
uint8_t isspace(char c);

// Check if character is uppercase letter
uint8_t isupper(char c);

// Check if character is hexadecimal digit
uint8_t isxdigit(char c);