#pragma once
#include <stdint.h>

struct stivale_header
{
    //stack pointer that's going to be loaded
    uint64_t stack;
    // Flags
    // bit 0   0 = text mode,   1 = graphics mode
    uint16_t flags;
    uint16_t framebuffer_width;
    uint16_t framebuffer_height;
    uint16_t framebuffer_bpp;
    uint64_t entry_point;
} __attribute__((packed));

enum stivale_memmap_entry_type
{
    USABLE = 1,
    RESERVED = 2,
    ACPIRECLAIM = 3,
    ACPINVS = 4
};

struct stivale_memmap_entry
{
    uint64_t base;
    uint64_t size;
    uint32_t type;
    uint32_t unused;
} __attribute__((packed));

struct stivale_memmap
{
    struct stivale_memmap_entry *address;
    uint64_t entries;
} __attribute__((packed));

struct stivale_framebuffer
{
    uint64_t address;
    uint16_t pitch;
    uint16_t width;
    uint16_t height;
    uint16_t bpp;
} __attribute__((packed));

struct stivale_module
{
    uint64_t begin;
    uint64_t end;
    char name[128];
    uint64_t next;
} __attribute__((packed));

struct stivale_struct
{
    char *cmdline;
    struct stivale_memmap memmap;
    struct stivale_framebuffer fb;
    uint64_t rsdp;
    uint64_t module_count;
    struct stivale_module module;
    uint64_t epoch;
} __attribute__((packed));