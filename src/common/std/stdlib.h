#pragma once

// char * conversion

// Convert string to long double
// Parses the C string str, interpreting its content as a floating point number and returns its value as a long double.
long double atold(const char *str);

// Convert string to double
// Parses the C string str, interpreting its content as a floating point number and returns its value as a double.
double atof(const char *str);

// Convert string to integer
// Parses the C-string str interpreting its content as an integral number, which is returned as a value of type int.
int atoi(const char *str);

// Convert string to long integer
// Parses the C-string str interpreting its content as an integral number, which is returned as a value of type long int.
long int atol(const char *str);

// Convert string to long long integer
// Parses the C-string str interpreting its content as an integral number, which is returned as a value of type long long int.
long long int atoll(const char *str);

// Convert string to double
// Parses the C-string str interpreting its content as a floating point number (according to the current locale) and returns its value as a double. If endptr is not a null pointer, the function also sets the value of endptr to point to the first character after the number.
double strtod(const char *str, char **endptr);

// Convert string to float
// Parses the C-string str interpreting its content as a floating point number (according to the current locale) and returns its value as a float. If endptr is not a null pointer, the function also sets the value of endptr to point to the first character after the number.
float strtof(const char *str, char **endptr);

// Convert string to long integer
// Parses the C-string str interpreting its content as an integral number of the specified base, which is returned as a long int value. If endptr is not a null pointer, the function also sets the value of endptr to point to the first character after the number.
long int strtol(const char *str, char **endptr, int base);

// Convert string to long double
// Parses the C string str interpreting its content as a floating point number (according to the current locale) and returns its value as a long double. If endptr is not a null pointer, the function also sets the value of endptr to point to the first character after the number.
long double strtold(const char *str, char **endptr);

// Convert string to long long integer
// Parses the C-string str interpreting its content as an integral number of the specified base, which is returned as a value of type long long int. If endptr is not a null pointer, the function also sets the value of endptr to point to the first character after the number.
long long int strtoll(const char *str, char **endptr, int base);

// Convert string to unsigned long integer
// Parses the C-string str, interpreting its content as an integral number of the specified base, which is returned as an value of type unsigned long int.
unsigned long int strtoul(const char *str, char **endptr, int base);

// Convert string to unsigned long long integer
// Parses the C-string str interpreting its content as an integral number of the specified base, which is returned as a value of type unsigned long long int. If endptr is not a null pointer, the function also sets the value of endptr to point to the first character after the number.
unsigned long long int strtoull(const char *str, char **endptr, int base);