%define SYS_WRITE 1
%define SYS_READ  0
%define FD_STDOUT 1
%define FD_STDIN  0
%define SYS_EXIT  60
%define SYS_TIME  201

global _start
default rel

section .bss
    COMPUTER_GEN: resq 1
    USER        : resq 1
    
section .rodata
    SUC_MSG : db "You win the game", 10
    SUC_LEN : equ $- SUC_MSG

    FAI_MSG : db "You failed the game", 10
    FAI_LEN : equ $- FAI_MSG

    WEL_MSG : db "Welcome to this game", 10
    WEL_LEN : equ $- WEL_MSG

    PRINT_PROMPT : db "You Entered ['1' for rock, '2' for paper, '3' for scissor] : "
    PROMPT_LEN   : equ $- PRINT_PROMPT

section .text
    
    _println:
        mov rax, SYS_WRITE
        mov rdi, FD_STDOUT
        mov rsi, rbx
        mov rdx, rcx
        syscall
        ret

    _input:
        mov rax, SYS_READ
        mov rdi, FD_STDIN
        mov rsi, rbx
        mov rdx, rcx
        syscall
        ret

    _random:
        mov rax, SYS_TIME
        xor rdi, rdi
        syscall

        xor rdx, rdx        ; RDX:RAX / 3
        mov rbx, 3
        div rbx             ; remainder in RDX = 0..2
        mov rax, rdx
        add rax, 1          ; 1..3
        add rax, '0'        ; ASCII '1'..'3'
        mov byte [COMPUTER_GEN], al
        ret

    _start:

        lea rbx, [rel WEL_MSG]
        mov rcx, WEL_LEN
        call _println
        jmp .while

        .while:

            lea rbx, [rel PRINT_PROMPT]
            mov rcx, PROMPT_LEN
            call _println

            ; read USER choice (1 byte: '1'/'2'/'3')
            lea rbx, [rel USER]
            mov rcx, 1
            call _input

            ; generate COMPUTER_GEN ('1'..'3' in ASCII)
            call _random

            ; load bytes and compare
            mov al, byte [COMPUTER_GEN]
            mov bl, byte [USER]
            cmp al, bl
            je .EQUAL_MATCH
            jmp .NOT_EQUAL

        .EQUAL_MATCH:
            lea rbx, [rel SUC_MSG]
            mov rcx, SUC_LEN
            call _println
            jmp .while

        .NOT_EQUAL:
            lea rbx, [rel FAI_MSG]
            mov rcx, FAI_LEN
            call _println
            jmp .while
