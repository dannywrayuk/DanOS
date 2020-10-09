#include <sys/exceptions.h>

#include <std/cstdio.h>

static const char *exceptions[] = {
    "Division by 0",
    "Debug",
    "NMI",
    "Breakpoint",
    "Overflow",
    "Bound range exceeded",
    "Invalid opcode",
    "Device not available",
    "Double fault",
    "",
    "Invalid TSS",
    "Segment not present",
    "Stack-segment fault",
    "General protection fault",
    "Page fault",
    "",
    "x87 exception",
    "Alignment check",
    "Machine check",
    "SIMD exception",
    "Virtualisation",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "Security"};

extern "C" void exception_handler(int exception, regs_t *regs, size_t error_code)
{
    std::printf("Oops! %s exception.\n", exceptions[exception]);
    asm volatile("hlt");
}