#pragma once
#include <stddef.h>

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

    // Convert integer to string (non-standard function)
    // Converts an integer value to a null-terminated string using the specified base and stores the result in the array given by str parameter.
    char *itoa(int value, char *str);
    char *itoa(int value, char *str, int base);
    char *itoa(int value, char *str, int base, int prefix);

    // Convert unsigned integer to string (non-standard function)
    // Converts an unsigned integer value to a null-terminated string using the specified base and stores the result in the array given by str parameter.
    char *utoa(unsigned int value, char *str);
    char *utoa(unsigned int value, char *str, int base);
    char *utoa(unsigned int value, char *str, int base, int prefix);

    // Convert double to string (non-standard function)
    // Converts a double value to a null-terminated string using the decimal precision specified and stores the result in the array given by str parameter.
    char *ftoa(double value, char *str, int afterpoint);

    // Pseudo-random sequence generation

    // Generate random number
    // Returns a pseudo-random integral number in the range between 0 and RAND_MAX.
    int rand(void);

    // Initialize random number generator
    // The pseudo-random number generator is initialized using the argument passed as seed.
    void srand(unsigned int seed);

    // Searching and sorting

    // Binary search in array
    // Searches the given key in the array pointed to by base (which is formed by num elements, each of size bytes), and returns a void* pointer to a matching element, if found.
    void *bsearch(const void *key, const void *base,
                  size_t num, size_t size,
                  int (*compar)(const void *, const void *));

    // Sort elements of array
    // Sorts the num elements of the array pointed to by base, each element size bytes long, using the compar function to determine the order.
    void qsort(void *base, size_t num, size_t size,
               int (*compar)(const void *, const void *));

    // Integer arithmetics

    // Absolute value
    // Returns the absolute value of parameter n ( /n/ ).
    int abs(int n);
    long int abs(long int n);
    long long int abs(long long int n);

} // namespace std