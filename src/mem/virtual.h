#pragma once
#include <stdint.h>
#include <boot/stivale.h>

#define PAGE_TABLE_ENTRIES 512
#define KERNEL_PHYS_OFFSET ((size_t)0xffffffff80000000)

namespace virt
{
    struct page
    {
        uint64_t present : 1;  // Page present in memory
        uint64_t rw : 1;       // Read-only if clear, readwrite if set
        uint64_t user : 1;     // Supervisor level only if clear
        uint64_t accessed : 1; // Has the page been accessed since last refresh?
        uint64_t dirty : 1;    // Has the page been written to since last refresh?
        uint64_t unused : 7;   // Amalgamation of unused and reserved bits
        uint64_t frame : 50;   // Frame address (shifted right 12 bits)
    };

    // page map level 4
    typedef uint64_t pml4_t;

    // page directory pointer
    typedef uint64_t pdpt_t;

    // page directory
    typedef uint64_t pd_t;

    // page table
    typedef uint64_t pt_t;

    void setPageMap(pml4_t newDir);

    void init(stivale_memmap *memmap);

} // namespace virt