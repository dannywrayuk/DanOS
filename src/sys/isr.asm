; Save registers.
%macro pusham 0
    cld
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
%endmacro

%macro popam 0
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
%endmacro

extern exceptionHandler

%macro isrHandler 1
    pusham
    mov rdi, %1
    mov rsi, rsp
    xor rdx, rdx
    ; Only reset rbp to limit trace if coming from userland
    mov rax, [rsp+16*8]
    cmp rax, 0x08
    je .nozerorbp
    xor rbp, rbp
  .nozerorbp:
    call exceptionHandler
    popam
    iretq
%endmacro

%macro isrHandlerError 1
    push qword [rsp+5*8]
    push qword [rsp+5*8]
    push qword [rsp+5*8]
    push qword [rsp+5*8]
    push qword [rsp+5*8]
    pusham
    mov rdi, %1
    mov rsi, rsp
    mov rdx, qword [rsp+20*8]
    ; Only reset rbp to limit trace if coming from userland
    mov rax, [rsp+16*8]
    cmp rax, 0x08
    je .nozerorbp
    xor rbp, rbp
  .nozerorbp:
    call exceptionHandler
    popam
    iretq
%endmacro

%macro defineISRHandler 1
global isr%1Handler
isr%1Handler:
    isrHandler %1
%endmacro

%macro defineISRHandlerError 1
global isr%1Handler
isr%1Handler:
    isrHandlerError %1
%endmacro

defineISRHandler 0
defineISRHandler 1
defineISRHandler 2
defineISRHandler 3
defineISRHandler 4
defineISRHandler 5
defineISRHandler 6
defineISRHandler 7
defineISRHandlerError 8
defineISRHandlerError 10
defineISRHandlerError 11
defineISRHandlerError 12
defineISRHandlerError 13
defineISRHandlerError 14
defineISRHandler 16
defineISRHandlerError 17
defineISRHandler 18
defineISRHandler 19
defineISRHandler 20
defineISRHandlerError 30


extern interruptHandler
%macro irqHandler 1
    pusham
    mov rdi, %1
    xor rbp, rbp
    call interruptHandler

    popam
    iretq
%endmacro

%macro defineIRQHandler 1
global irq%1Handler
irq%1Handler:
    irqHandler %1
%endmacro

defineIRQHandler 0
defineIRQHandler 1