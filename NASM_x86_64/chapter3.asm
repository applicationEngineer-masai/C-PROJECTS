global _start
default rel

%define SYS_WRITE 1
%define SYS_EXIT  60

section .rodata
nl:  db 10

section .text
; expects: RSI=buf, RDX=len
write_buf:
    mov     rax, SYS_WRITE
    mov     rdi, 1            ; fd = stdout
    syscall
    ret

print_digit:
    add     dil, '0'          ; make ASCII
    push    rdi               ; put 1 byte (low) on stack
    mov     rsi, rsp          ; buffer ptr = top of stack
    mov     rdx, 1            ; length = 1
    call    write_buf
    pop     rdi               ; restore
    ret

newline:
    lea     rsi, [rel nl]
    mov     rdx, 1
    call    write_buf
    ret

_start:
    mov     rdi, 5
    call    print_digit
    mov     rdi, 6
    call    print_digit
    call    newline

    ; exit(0)
    mov     rax, SYS_EXIT
    xor     rdi, rdi
    syscall

section .note.GNU-stack noalloc noexec nowrite
