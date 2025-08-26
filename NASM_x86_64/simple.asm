
; simple.asm
; build "nasm -felf64 simple.asm -o simple.o"
; link : "ld -o simple simple.o"
; run :  ./simple

    global _start

    section .data

msg: db "Hello, World, By Asm!", 10 ; 10 = newline
len: equ $ - msg ; assembly runtime length

    section .text
_start:
    ; write (1, msg, len)
    mov rax, 1 ; sys_write 1
    mov rdi, 1 ; fd = 1 (stdout)
    mov rsi, msg ; load buff
    mov rdx, len ; count
    syscall ; 

    ; exit(0)
    mov rax, 60 ;sys_exit = 60
    xor rdi, rdi ;status = 0
    syscall