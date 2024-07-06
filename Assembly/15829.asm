    section .rodata
input_format_len  db      "%d", 0, 0
input_format_str  db      "%s", 0, 0
output_format     db      "%d", 10, 0

    section .bss
input_buffer      resb    64
power_array       resd    64

    section .text
    extern  scanf
    extern  printf
    global  main
main:
    push    ebp
    mov     ebp, esp
    sub     esp, 16
    and     esp, -16
    push    ebx
    push    esi
    push    edi

    mov     ebx, 1234567891  
    mov     esi, input_buffer

    lea     eax, [ebp - 4]
    push    eax
    push    input_format_len
    call    scanf
    add     esp, 8

    push    input_buffer
    push    input_format_str
    call    scanf
    add     esp, 8

    push    ebx
    push    DWORD [ebp - 4]
    push    31
    call    calculate_power_mod
    add     esp, 12

    xor     eax, eax
    mov     DWORD [ebp - 8], eax
    mov     edi, power_array
    xor     ecx, ecx
.sum_loop:
    cmp     cl, BYTE [ebp - 4]
    jnl     .end_sum_loop

    xor     eax, eax
    mov     al, BYTE [esi + 1 * ecx]
    sub     al, 0x60
    imul    DWORD [edi + 4 * ecx]
    idiv    ebx
    add     edx, DWORD [ebp - 8]
    mov     eax, edx
    xor     edx, edx
    setc    dl
    idiv    ebx
    mov     DWORD [ebp - 8], edx
    inc     ecx
    jmp     .sum_loop

.end_sum_loop:
    push    edx
    push    output_format
    call    printf
    add     esp, 8

    xor     eax, eax
    pop     edi
    pop     esi
    pop     ebx
    leave
    ret

calculate_power_mod:
    push    ebp
    mov     ebp, esp
    push    ebx
    push    esi
    push    edi

    mov     esi, DWORD [ebp + 16]
    mov     edi, power_array
    mov     eax, DWORD [ebp + 8]
    cdq
    idiv    esi
    mov     ebx, edx

    xor     ecx, ecx
    xor     eax, eax
    inc     eax
.power_loop:
    cmp     ecx, DWORD [ebp + 12]
    jnl     .end_power_loop

    mov     DWORD [edi + 4 * ecx], eax
    imul    ebx
    idiv    esi
    mov     eax, edx
    inc     ecx
    jmp     .power_loop

.end_power_loop:
    pop     edi
    pop     esi
    pop     ebx
    leave
    ret
