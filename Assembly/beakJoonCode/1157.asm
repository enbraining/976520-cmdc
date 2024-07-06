    section .rodata
fmt_in      db      "%s"

    section .bss
count       resd    26
            alignb  16
most_used   resd    4
    ;  0: The most used letter
    ;  4: And its count
    ;  8: The next most used letter
    ; 12: ...and its count, too

buf         resb    1000001

    section .text
    extern  scanf
    extern  putchar
    global  main
main:
    push    ebp
    mov     ebp, esp
    push    ebx
    push    esi
    push    edi

    mov     esi, buf
    mov     edi, count

    push    esi
    push    fmt_in
    call    scanf
    add     esp, 8

    xor     eax, eax
    xor     ecx, ecx
    xor     edx, edx
    mov     dl, 32
.count_loop:
    mov     al, BYTE [esi + 1 * ecx]
    test    al, al
    jz      .end_count_loop

    xor     ebx, ebx
    cmp     al, 96
    cmovg   ebx, edx
    sub     al, bl
    sub     al, 65
    inc     DWORD [edi + 4 * eax]
    inc     ecx
    jmp     .count_loop

.end_count_loop:
    mov     esi, edi
    mov     edi, most_used

    xor     eax, eax
    dec     eax
    movd    xmm0, eax
    pshufd  xmm0, xmm0, 0x00
    movaps  [edi], xmm0

    xor     ecx, ecx
.select_loop:
    cmp     cl, 26
    jnl     .end_select_loop

    mov     eax, DWORD [esi + 4 * ecx]
    cmp     eax, DWORD [edi + 4]
    jl      .continue_select_loop

    movaps  xmm0, [edi]
    pshufd  xmm0, xmm0, 0x4E
    movaps  [edi], xmm0
    mov     DWORD [edi], ecx
    mov     DWORD [edi + 4], eax
    xor     eax, eax
    mov     DWORD [esi + 4 * ecx], eax

.continue_select_loop:
    inc     ecx
    jmp     .select_loop

.end_select_loop:
    add     BYTE [edi], 65
    mov     bl, 63
    mov     ecx, DWORD [edi + 4]
    mov     edx, DWORD [edi + 12]
    cmp     ecx, edx
    cmove   eax, ebx
    cmovne  eax, DWORD [edi]

    push    10
    push    eax
    call    putchar
    add     esp, 4
    call    putchar
    add     esp, 4

    xor     eax, eax
    pop     edi
    pop     esi
    pop     ebx
    leave
    ret
