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

extern exception_handler

%macro except_handler 1
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
    call exception_handler
    popam
    iretq
%endmacro

%macro except_handler_err_code 1
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
    call exception_handler
    popam
    iretq
%endmacro


global div0_handler
global debug_handler
global nmi_handler
global breakpoint_handler
global overflow_handler
global bound_range_handler
global inv_opcode_handler
global no_dev_handler
global double_fault_handler
global inv_tss_handler
global no_segment_handler
global ss_fault_handler
global gpf_handler
global page_fault_handler
global x87_fp_handler
global alignment_check_handler
global machine_check_handler
global simd_fp_handler
global virt_handler
global security_handler

div0_handler:
    except_handler 0x0
debug_handler:
    except_handler 0x1
nmi_handler:
    except_handler 0x2
breakpoint_handler:
    except_handler 0x3
overflow_handler:
    except_handler 0x4
bound_range_handler:
    except_handler 0x5
inv_opcode_handler:
    except_handler 0x6
no_dev_handler:
    except_handler 0x7
double_fault_handler:
    except_handler_err_code 0x8
inv_tss_handler:
    except_handler_err_code 0xa
no_segment_handler:
    except_handler_err_code 0xb
ss_fault_handler:
    except_handler_err_code 0xc
gpf_handler:
    except_handler_err_code 0xd
page_fault_handler:
    except_handler_err_code 0xe
x87_fp_handler:
    except_handler 0x10
alignment_check_handler:
    except_handler_err_code 0x11
machine_check_handler:
    except_handler 0x12
simd_fp_handler:
    except_handler 0x13
virt_handler:
    except_handler 0x14
security_handler:
    except_handler_err_code 0x1e

align 16
global irq0_handler
irq0_handler:
    pusham

    extern tick_handler
    xor rbp, rbp
    call tick_handler

    popam
    iretq

global irq1_handler
irq1_handler:
    pusham

    extern key_handler
    xor rbp, rbp
    call key_handler

    popam
    iretq