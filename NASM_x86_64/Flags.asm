
; using flags ZF (jum if not equal)

section .rodata
    msg_equal: db "Yes Both are Equal", 10
    msg_equal_len: equ $- msg_equal
    
    msg_nequal: db "No Both are Not Equals", 10
    msg_nequal_len: equ $- msg_nequal

section .data
    
    Num1: dq 20
    Num2: dq 10

section .text
    global _start

_start:
    mov rax, [Num1]
    mov rbx, [Num2]
    cmp rax, rbx
    je _L_jump_equal ; jump if equal
    jne _Lnot_equal ; else equal

_Lnot_equal:
    mov rax, 1 ; write system call
    mov rdi, 1 ; fd=1, stdout
    lea rsi, [rel msg_nequal]
    mov rdx, msg_nequal_len
    syscall
    jmp _exit

_L_jump_equal:
    mov rax, 1 ; write system call
    mov rdi, 1 ; fd=1, stdout
    lea rsi, [rel msg_equal]
    mov rdx, msg_equal_len
    syscall
    jmp _exit

_exit:
    mov rax, 60 ; exit system call
    xor rdi, rdi ; exit code 0
    syscall
