#pragma once
#include <stdint.h>

struct regs_t
{
    uint64_t r15;
    uint64_t r14;
    uint64_t r13;
    uint64_t r12;
    uint64_t r11;
    uint64_t r10;
    uint64_t r9;
    uint64_t r8;
    uint64_t rbp;
    uint64_t rdi;
    uint64_t rsi;
    uint64_t rdx;
    uint64_t rcx;
    uint64_t rbx;
    uint64_t rax;
    uint64_t rip;
    uint64_t cs;
    uint64_t rflags;
    uint64_t rsp;
    uint64_t ss;
};

extern "C" void div0_handler();
extern "C" void debug_handler();
extern "C" void nmi_handler();
extern "C" void breakpoint_handler();
extern "C" void overflow_handler();
extern "C" void bound_range_handler();
extern "C" void inv_opcode_handler();
extern "C" void no_dev_handler();
extern "C" void double_fault_handler();
extern "C" void inv_tss_handler();
extern "C" void no_segment_handler();
extern "C" void ss_fault_handler();
extern "C" void gpf_handler();
extern "C" void page_fault_handler();
extern "C" void x87_fp_handler();
extern "C" void alignment_check_handler();
extern "C" void machine_check_handler();
extern "C" void simd_fp_handler();
extern "C" void virt_handler();
extern "C" void security_handler();

extern "C" void irq0_handler();
extern "C" void irq1_handler();