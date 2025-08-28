%define SYS_EXIT   60
%define SYS_READ    0
%define SYS_WRITE   1
%define SYS_TIME  201

global _start
default rel

section .rodata
MSG_PROMPT:     db "Enter Your Guess!", 10
MSG_PROMPT_LEN: equ $ - MSG_PROMPT

MSG_LOW:        db "TOO Low Number!", 10
MSG_LOW_LEN:    equ $ - MSG_LOW

MSG_HIGH:       db "TOO High Number!", 10
MSG_HIGH_LEN:   equ $ - MSG_HIGH

MSG_OK:         db "TOO Correct Guess!", 10
MSG_OK_LEN:     equ $ - MSG_OK

NL:             db 10

section .bss
user:   resb 32            ; input buffer
buf:    resb 32            ; print_num scratch

section .text

; write(fd=1, rsi=buf, rdx=len)
print_str:
    mov     rax, SYS_WRITE
    mov     rdi, 1
    syscall
    ret

; RAX = unsigned integer to print (also prints newline)
print_num:
    mov     rbx, 10
    lea     rdi, [buf+32]  ; rdi points one past the end
  .convert:
    xor     rdx, rdx
    div     rbx            ; (RDX:RAX)/10 -> RAX=quot, RDX=rem
    dec     rdi
    add     dl, '0'
    mov     [rdi], dl
    test    rax, rax
    jnz     .convert

    ; write digits
    mov     rsi, rdi
    lea     rdx, [buf+32]
    sub     rdx, rsi
    call    print_str

    ; newline
    lea     rsi, [rel NL]
    mov     rdx, 1
    call    print_str
    ret

; returns random 0..99 in RAX
get_random_number:
    mov     rax, SYS_TIME
    xor     rdi, rdi
    syscall                 ; RAX = epoch seconds
    mov     rbx, 100
    xor     rdx, rdx
    div     rbx             ; RDX = remainder 0..99
    mov     rax, rdx
    ret

; Parse decimal from user buffer → RAX
; stops at newline or first non-digit
parse_user_number:
    xor     rax, rax                ; result = 0
    lea     rsi, [rel user]
  .loop:
    mov     bl, [rsi]
    cmp     bl, 10                  ; newline?
    je      .done
    cmp     bl, '0'
    jb      .skip
    cmp     bl, '9'
    ja      .skip
    imul    rax, rax, 10
    movzx   rdx, bl
    sub     rdx, '0'
    add     rax, rdx
  .skip:
    inc     rsi
    jmp     .loop
  .done:
    ret

; read up to 32 bytes into 'user'
read_line:
    mov     rax, SYS_READ
    xor     rdi, rdi                ; fd=0
    lea     rsi, [rel user]
    mov     rdx, 32
    syscall
    ret

_start:
  .while:
    ; prompt
    lea     rsi, [rel MSG_PROMPT]
    mov     rdx, MSG_PROMPT_LEN
    call    print_str

    ; read user line
    call    read_line

    ; parse user number -> RAX
    call    parse_user_number
    mov     r8, rax                 ; r8 = user guess

    ; random 0..99 -> RAX
    call    get_random_number
    mov     r9, rax                 ; r9 = secret

    ; compare
    cmp     r8, r9
    je      .match
    jb      .too_low                ; (unsigned below) or use jl for signed
    ; else: r8 > r9
    jmp     .too_high

  .too_low:
    lea     rsi, [rel MSG_LOW]
    mov     rdx, MSG_LOW_LEN
    call    print_str
    jmp     .while

  .too_high:
    lea     rsi, [rel MSG_HIGH]
    mov     rdx, MSG_HIGH_LEN
    call    print_str
    jmp     .while

  .match:
    lea     rsi, [rel MSG_OK]
    mov     rdx, MSG_OK_LEN
    call    print_str

    ; (optional) print secret number:
    ; mov   rax, r9
    ; call  print_num

    ; exit(0)
    mov     rax, SYS_EXIT
    xor     rdi, rdi
    syscall

section .note.GNU-stack noalloc noexec nowrite
