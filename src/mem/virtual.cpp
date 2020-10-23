#include <mem/virtual.h>
#include <mem/physical.h>
#include <mem/cmem.h>
#include <std/cstdio.h>

#define writeCR(reg, val) ({          \
    asm volatile("mov cr" #reg ", %0" \
                 :                    \
                 : "r"(val));         \
})

#define readCR(reg) ({             \
    size_t cr;                     \
    asm volatile("mov %0, cr" #reg \
                 : "=r"(cr));      \
    cr;                            \
})

#define invlpg(addr) ({ \
    asm volatile(       \
        "invlpg [%0];"  \
        :               \
        : "r"(addr));   \
})

namespace virt
{
    pml4_t *kernelPageMap = 0;

    int unmapPage(pml4_t *pageMap, size_t virtualAddress)
    {
        pml4_t pml4Index = (virtualAddress & ((size_t)0x1ff << 39)) >> 39;
        pdpt_t pdptIndex = (virtualAddress & ((size_t)0x1ff << 30)) >> 30;
        pd_t pdIndex = (virtualAddress & ((size_t)0x1ff << 21)) >> 21;
        pt_t ptIndex = (virtualAddress & ((size_t)0x1ff << 12)) >> 12;

        pdpt_t *pdpt;
        pd_t *pd;
        pt_t *pt;

        if (pageMap[pml4Index] & 0x1)
        {
            pdpt = (pdpt_t *)((pageMap[pml4Index] & 0xfffffffffffff000) + MEM_PHYS_OFFSET);
        }
        else
        {
            std::printf("MapPage failed\n");
            return -1;
        }

        if (pdpt[pdptIndex] & 0x1)
        {
            pd = (pd_t *)((pdpt[pdptIndex] & 0xfffffffffffff000) + MEM_PHYS_OFFSET);
        }
        else
        {
            std::printf("MapPage failed\n");
            return -1;
        }

        if (pd[pdIndex] & 0x1)
        {
            pt = (pt_t *)((pd[pdIndex] & 0xfffffffffffff000) + MEM_PHYS_OFFSET);
        }
        else
        {
            std::printf("MapPage failed\n");
            return -1;
        }

        pt[ptIndex] = 0;

        if ((size_t)pageMap == readCR(3))
        {
            // TODO: TLB shootdown
            invlpg(virtualAddress);
        }

        /* Free previous levels if empty */
        for (size_t i = 0;; i++)
        {
            if (i == PAGE_TABLE_ENTRIES)
            {
                /* We reached the end, table is free */
                phys::free((size_t *)pt - MEM_PHYS_OFFSET, 1);
                break;
            }
            if (pt[i] & 0x1)
            {
                /* Table is not free */
                return 0;
            }
        }

        for (size_t i = 0;; i++)
        {
            if (i == PAGE_TABLE_ENTRIES)
            {
                /* We reached the end, table is free */
                phys::free((size_t *)pd - MEM_PHYS_OFFSET, 1);
                break;
            }
            if (pd[i] & 0x1)
            {
                /* Table is not free */
                return 0;
            }
        }

        for (size_t i = 0;; i++)
        {
            if (i == PAGE_TABLE_ENTRIES)
            {
                /* We reached the end, table is free */
                phys::free((size_t *)pdpt - MEM_PHYS_OFFSET, 1);
                break;
            }
            if (pdpt[i] & 0x1)
            {
                /* Table is not free */
                return 0;
            }
        }
        return 0;
    }

    int mapPage(pml4_t *pageMap, uint64_t physicalAddress, uint64_t virtualAddress, size_t flags)
    {
        pml4_t pml4Index = (virtualAddress & ((size_t)0x1ff << 39)) >> 39;
        pdpt_t pdptIndex = (virtualAddress & ((size_t)0x1ff << 30)) >> 30;
        pd_t pdIndex = (virtualAddress & ((size_t)0x1ff << 21)) >> 21;
        pt_t ptIndex = (virtualAddress & ((size_t)0x1ff << 12)) >> 12;

        pdpt_t *pdpt;
        pd_t *pd;
        pt_t *pt;

        if (pageMap[pml4Index] & 0x1)
        {
            pdpt = (pdpt_t *)((pageMap[pml4Index] & 0xfffffffffffff000) + MEM_PHYS_OFFSET);
        }
        else
        {
            pdpt = (pdpt_t *)((char *)phys::allocz(1) + MEM_PHYS_OFFSET);
            if ((size_t)pdpt == MEM_PHYS_OFFSET)
            {
                std::printf("MapPage failed\n");
                return -1;
            }
            pageMap[pml4Index] = (pml4_t)((size_t)pdpt - MEM_PHYS_OFFSET) | 0b111;
        }

        if (pdpt[pdptIndex] & 0x1)
        {
            pd = (pd_t *)((pdpt[pdptIndex] & 0xfffffffffffff000) + MEM_PHYS_OFFSET);
        }
        else
        {
            pd = (pdpt_t *)((char *)phys::allocz(1) + MEM_PHYS_OFFSET);
            if ((size_t)pd == MEM_PHYS_OFFSET)
            {
                std::printf("MapPage failed\n");
                return -1;
            }
            pdpt[pdptIndex] = (pdpt_t)((size_t)pd - MEM_PHYS_OFFSET) | 0b111;
        }

        if (pd[pdIndex] & 0x1)
        {
            pt = (pt_t *)((pd[pdIndex] & 0xfffffffffffff000) + MEM_PHYS_OFFSET);
        }
        else
        {
            pt = (pt_t *)((char *)phys::allocz(1) + MEM_PHYS_OFFSET);
            if ((size_t)pt == MEM_PHYS_OFFSET)
            {
                std::printf("MapPage failed\n");
                return -1;
            }
            pd[pdIndex] = (pd_t)((size_t)pt - MEM_PHYS_OFFSET) | 0b111;
        }

        pt[ptIndex] = (pt_t)(physicalAddress | flags);

        if ((size_t)pageMap == readCR(3))
        {
            invlpg(virtualAddress);
        }

        return 0;
    }

    void init(stivale_memmap *memmap)
    {
        kernelPageMap = (pml4_t *)((char *)phys::allocz(1) + MEM_PHYS_OFFSET);
        for (size_t i = 0; i < (0x2000000 / PAGE_SIZE); i++)
        {
            size_t addr = i * PAGE_SIZE;
            mapPage(kernelPageMap, addr, addr, 0x03);
            mapPage(kernelPageMap, addr, MEM_PHYS_OFFSET + addr, 0x03);
            mapPage(kernelPageMap, addr, KERNEL_PHYS_OFFSET + addr, 0x03 | (1 << 8));
        }

        writeCR(3, (size_t)kernelPageMap - MEM_PHYS_OFFSET);

        for (size_t i = 0; i < (0x100000000 / PAGE_SIZE); i++)
        {
            size_t addr = i * PAGE_SIZE;
            mapPage(kernelPageMap, addr, MEM_PHYS_OFFSET + addr, 0x03);
        }

        for (size_t i = 0; i < memmap->entries; i++)
        {
            struct stivale_memmap_entry *entry = &(memmap->address[i]);
            size_t aligned_base = entry->base - (entry->base % PAGE_SIZE);
            size_t aligned_length = (((entry->size) + ((PAGE_SIZE)-1)) / (PAGE_SIZE)) * PAGE_SIZE;

            if (entry->base % PAGE_SIZE)
                aligned_length += PAGE_SIZE;

            for (size_t j = 0; j * PAGE_SIZE < aligned_length; j++)
            {
                size_t addr = aligned_base + j * PAGE_SIZE;

                /* Skip over first 4 GiB */
                if (addr < 0x100000000)
                    continue;
                mapPage(kernelPageMap, addr, MEM_PHYS_OFFSET + addr, 0x03);
            }
        }

        std::printf(" %Cg✓%C0  Virtual Memory.\n");
    }
} // namespace virt