section .data
    input_format  db  "%d", 0
    output_format db  "%d", 10, 0

section .bss
    number_string resb    8
    count         resd    1

section .text
    global  main
    extern  scanf
    extern  printf
    extern  snprintf

main:
    push    ebp
    mov     ebp, esp
    sub     esp, 16
    and     esp, -16

    lea     eax, [ebp-4]
    push    eax
    push    input_format
    call    scanf

    xor     ecx, ecx
    mov     cl, 1
.loop:
    cmp     ecx, dword [ebp-4]
    jg      .end_loop
    cmp     ecx, 100
    jl      .check_and_increment

    push    ecx
    call    is_number_valid
    pop     ecx
    test    al, al
    jnz     .check_and_increment

    inc     ecx
    jmp     .loop

.check_and_increment:
    inc     dword [count]
    inc     ecx
    jmp     .loop

.end_loop:
    push    dword [count]
    push    output_format
    call    printf
    add     esp, 8

    xor     eax, eax
    leave
    ret

global  is_number_valid
is_number_valid:
    push    dword [esp+4]    ; parameter: length
    push    input_format     ; format string
    push    8                 ; buffer size
    push    number_string    ; buffer
    call    snprintf
    add     esp, 16
    dec     eax              ; return value is adjusted for comparison

    movq    mm0, qword [number_string]
    movq    mm1, mm0
    psrlq   mm1, 8
    psubb   mm1, mm0
    movq    qword [number_string], mm1

    xor     ecx, ecx
.loop:
    cmp     cl, al
    jnl     .end_loop
    mov     dl, byte [number_string+ecx*1]
    cmp     dl, byte [number_string]
    jne     .no_match
    inc     ecx
    jmp     .loop

.no_match:
    xor     eax, eax
    ret

.end_loop:
    mov     eax, 1
    ret
