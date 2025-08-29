
; common.inc

; common system call for to invoke os-kernel

%define SYS_READ 0
%define SYS_WRITE 1
%define SYS_OPEN 2
%define SYS_CLOSE 3
%define SYS_PREAD 4
%define SYS_EXIT 60
$define O_RDONLY 0

%macro sys 1
    mov rax, %1
    syscall
%endmacro

section .data
    hexchars: db "0123456789ABCDEF"
    nl: db 10
    nl_len: equ $- nl
    
section .text
    ; rdi=fd, rsi=buf, rdx=len
    write_buf:
        mov rax, SYS_WRITE
        syscall
        ret

    ; rsi=ptr, rdx=len
    puts:
        mov rdi, 1
        mov rax, SYS_WRITE
        syscall
        ret

    putnl:
        mov rdi, 1
        lea rsi, [rel nl]
        mov rdx, nl_len
        mov rax, SYS_WRITE
        syscall
        ret
    