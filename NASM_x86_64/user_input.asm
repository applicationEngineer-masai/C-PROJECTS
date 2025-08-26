

    global _start

section .bss
    buffer : resb 128 ; reserve 128 bytes for user input

section .data
    prompt : db "Can You Just Give me, input : ", 10 ; 10 = newline
    plen : equ $ - prompt ; defining a constant variable plen to hold prompt length

section .text
    _start:
        ; C language equivalent : write(fd, buff, length)
        mov rax, 1 ; syscall number load in rax
        mov rdi, 1 ; fd = 1
        lea rsi, [rel prompt] ; load prompt relative address
        mov rdx, plen ; get length of the data (prompt)

        syscall

        ; C = read(0, buffer, 128)

        mov rax, 0 ; invoke read system call
        mov rdi, 0 ; fd = 0
        lea rsi, [rel buffer] ; load buffer relative address
        mov rdx, 128 ; load length of buffer
        syscall

        mov rbx, rax ; save the length in base register

        ; C = write(1, buffer, 128)

        mov rax, 1 ; invoke write system call to print input
        mov rdx, 1 ; invoke fd in data register
        lea rsi, [rel buffer] ; load buffer relative address in source register
        mov rdx, rbx ; load buffer size
        syscall ; invoke kernel to display

        ; exit(0)
        mov rax, 60 ; sys_exit
        xor rdi, rdi
        syscall