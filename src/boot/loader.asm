MBALIGN  equ  1 << 0            ; align loaded modules on page boundaries
MEMINFO  equ  1 << 1            ; provide memory map
VIDINFO  equ  1 << 2	        ; control video mode
FLAGS    equ  MBALIGN | MEMINFO | VIDINFO 
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + FLAGS)   ; checksum of above, to prove we are multiboot

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

	dd 0, 0, 0, 0, 0
	dd 0 ; 0 = set graphics mode
	dd 0, 0, 0 ; Width, height, depth



section .text
align 32

; Entry Point
global LOADER
extern KMAIN
LOADER:
	mov esp, STACK_TOP

	push 0
	popf

	push ebx
	push eax
    sti
	call KMAIN
	cli


.HANG:	hlt
	jmp .HANG

section .bss
STACK_BOTTOM:
	resb 16384 ; 16 KiB
STACK_TOP: