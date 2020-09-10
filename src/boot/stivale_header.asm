section .stivalehdr

align 4

stivale_header:
    dq STACK.TOP    ; Stack pointer
    dw 0            ; Video mode: 0=text, 1=VESA
    dw 0            ; Framebuffer Width: 0 for default.
    dw 0            ; Framebuffer Height: 0 for default.
    dw 0            ; Framebuffer bpp: 0 for default.
    dq 0            ; entry

section .bss

align 16
STACK:
    .BOTTOM:
    resb 32768
    .TOP: