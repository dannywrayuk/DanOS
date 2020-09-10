#include <std/ctype.h>

// Control codes
#define CTRL_START 0x00
#define CTRL_END 0x08
#define TAB 0x09
#define WHITE_SPACE_START 0x0A
#define WHITE_SPACE_END 0x0D
#define CTRL2_START 0x0E
#define CTRL2_END 0x1F
#define SPACE 0x20
#define PUNCTUATION_START 0x21
#define PUNCTUATION_END 0x2F
#define NUM_START 0x30
#define NUM_END 0x39
#define PUNCTUATION2_START 0x3A
#define PUNCTUATION2_END 0x40
#define AF_START 0x41
#define AF_END 0x46
#define GZ_START 0x47
#define GZ_END 0x5A
#define PUNCURATION3_START 0x5B
#define PUNCURATION3_END 0x60
#define af_START 0x61
#define af_END 0x66
#define gz_START 0x67
#define gz_END 0x7A
#define PUNCTUATION4_START 0x7B
#define PUNCTUATION4_END 0x7E
#define DEL 0x7F

uint8_t isalnum(char c)
{
    if (c >= af_START && c <= gz_END ||
        c >= AF_START && c <= GZ_END ||
        c >= NUM_START && c <= NUM_END)
    {
        return 1;
    }
    return 0;
}

uint8_t isalpha(char c)
{
    if (c >= af_START && c <= gz_END ||
        c >= AF_START && c <= GZ_END)
    {
        return 1;
    }
    return 0;
}

uint8_t isblank(char c)
{
    if (c == TAB || c == SPACE)
    {
        return 1;
    }
    return 0;
}

uint8_t iscntrl(char c)
{
    if (c >= CTRL_START && c <= CTRL2_END || c == DEL)
    {
        return 1;
    }
    return 0;
}

uint8_t isdigit(char c)
{
    if (c >= NUM_START && c <= NUM_END)
    {
        return 1;
    }
    return 0;
}

uint8_t isgraph(char c)
{
    if (c >= PUNCTUATION_START && c <= PUNCTUATION4_END)
    {
        return 1;
    }
    return 0;
}

uint8_t islower(char c)
{
    if (c >= af_START && c <= gz_END)
    {
        return 1;
    }
    return 0;
}

uint8_t ispruint8_t(char c)
{
    if (c >= SPACE && c <= PUNCTUATION4_END)
    {
        return 1;
    }
    return 0;
}

uint8_t ispunct(char c)
{
    if (c >= PUNCTUATION_START && c <= PUNCTUATION_END ||
        c >= PUNCTUATION2_START && c <= PUNCTUATION2_END ||
        c >= PUNCURATION3_START && c <= PUNCURATION3_END ||
        c >= PUNCTUATION4_START && c <= PUNCTUATION4_END)
    {
        return 1;
    }
    return 0;
}

uint8_t isspace(char c)
{
    if (c == TAB ||
        c >= WHITE_SPACE_START && c <= WHITE_SPACE_END ||
        c == SPACE)
    {
        return 1;
    }
    return 0;
}

uint8_t isupper(char c)
{
    if (c >= AF_START && c <= GZ_END)
    {
        return 1;
    }
    return 0;
}

uint8_t isxdigit(char c)
{
    if (c >= NUM_START && c <= NUM_END ||
        c >= AF_START && c <= AF_END ||
        c >= af_START && c <= af_END)
    {
        return 1;
    }
    return 0;
}