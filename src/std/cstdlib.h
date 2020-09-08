#pragma once
#include <stdint.h>
#include <stddef.h>

#define RAND_MAX UINT_MAX

namespace std
{

    // char * conversion

    // Convert string to long double
    // Parses the C string str, interpreting its content as a floating point number and returns its value as a long double.
    long double atold(const char *str);

    // Convert string to double
    // Parses the C string str, interpreting its content as a floating point number and returns its value as a double.
    double atof(const char *str);

    // Convert string to integer
    // Parses the C-string str interpreting its content as an integral number, which is returned as a value of type int.
    int16_t atoi(const char *str);

    // Convert string to long integer
    // Parses the C-string str interpreting its content as an integral number, which is returned as a value of type long int.
    int32_t atol(const char *str);

    // Convert string to long long integer
    // Parses the C-string str interpreting its content as an integral number, which is returned as a value of type long long int.
    int64_t atoll(const char *str);

    // Convert string to double
    // Parses the C-string str interpreting its content as a floating point number (according to the current locale) and returns its value as a double. If endptr is not a null pointer, the function also sets the value of endptr to point to the first character after the number.
    double strtod(const char *str, char **endptr);

    // Convert string to float
    // Parses the C-string str interpreting its content as a floating point number (according to the current locale) and returns its value as a float. If endptr is not a null pointer, the function also sets the value of endptr to point to the first character after the number.
    float strtof(const char *str, char **endptr);

    // Convert string to long integer
    // Parses the C-string str interpreting its content as an integral number of the specified base, which is returned as a long int value. If endptr is not a null pointer, the function also sets the value of endptr to point to the first character after the number.
    int32_t strtol(const char *str, char **endptr, int base);

    // Convert string to long double
    // Parses the C string str interpreting its content as a floating point number (according to the current locale) and returns its value as a long double. If endptr is not a null pointer, the function also sets the value of endptr to point to the first character after the number.
    long double strtold(const char *str, char **endptr);

    // Convert string to long long integer
    // Parses the C-string str interpreting its content as an integral number of the specified base, which is returned as a value of type long long int. If endptr is not a null pointer, the function also sets the value of endptr to point to the first character after the number.
    int64_t strtoll(const char *str, char **endptr, uint8_t base);

    // Convert string to unsigned long integer
    // Parses the C-string str, interpreting its content as an integral number of the specified base, which is returned as an value of type unsigned long int.
    uint32_t strtoul(const char *str, char **endptr, uint8_t base);

    // Convert string to unsigned long long integer
    // Parses the C-string str interpreting its content as an integral number of the specified base, which is returned as a value of type unsigned long long int. If endptr is not a null pointer, the function also sets the value of endptr to point to the first character after the number.
    uint64_t strtoull(const char *str, char **endptr, uint8_t base);

    // Convert integer to string (non-standard function)
    // Converts an integer value to a null-terminated string using the specified base and stores the result in the array given by str parameter.
    char *itoa(int64_t value, char *str);
    char *itoa(int64_t value, char *str, uint8_t base);
    char *itoa(int64_t value, char *str, uint8_t base, uint8_t prefix);

    // Convert unsigned integer to string (non-standard function)
    // Converts an unsigned integer value to a null-terminated string using the specified base and stores the result in the array given by str parameter.
    char *utoa(uint64_t value, char *str);
    char *utoa(uint64_t value, char *str, uint8_t base);
    char *utoa(uint64_t value, char *str, uint8_t base, uint8_t prefix);

    // Convert double to string (non-standard function)
    // Converts a double value to a null-terminated string using the decimal precision specified and stores the result in the array given by str parameter.
    char *ftoa(double value, char *str, uint8_t afterpoint);

    // Pseudo-random sequence generation

    // Generate random number
    // Returns a pseudo-random integral number in the range between 0 and RAND_MAX.
    uint32_t rand(void);

    // Initialize random number generator
    // The pseudo-random number generator is initialized using the argument passed as seed.
    void srand(uint32_t seed);

    // Searching and sorting

    // Binary search in array
    // Searches the given key in the array pointed to by base (which is formed by num elements, each of size bytes), and returns a void* pointer to a matching element, if found.
    void *bsearch(const void *key, const void *base,
                  size_t num, size_t size,
                  uint32_t (*compar)(const void *, const void *));

    // Sort elements of array
    // Sorts the num elements of the array pointed to by base, each element size bytes long, using the compar function to determine the order.
    void qsort(void *base, size_t num, size_t size,
               uint32_t (*compar)(const void *, const void *));

    // Integer arithmetics

    // Absolute value
    // Returns the absolute value of parameter n ( /n/ ).
    uint64_t abs(int64_t n);

} // namespace std