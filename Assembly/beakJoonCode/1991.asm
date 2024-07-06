section .rodata
fmt_in_int      db      "%d", 0, 0
fmt_in_ch       db      " %c", 0
fmt_in_ch2      db      " %c %c", 0, 0

section .bss
            alignb  16
nodes       resb    2 * 32
outbuf      resb    32
outbuf2     resb    32
outbuf3     resb    32

section .text
extern  scanf
extern  puts
global  main

main:
    push    ebp
    mov     ebp, esp
    sub     esp, 16
    and     esp, -16
    push    ebx
    push    esi
    push    edi

    lea     eax, [ebp - 4]
    push    eax
    push    fmt_in_int
    call    scanf
    add     esp, 8

    mov     edi, nodes
    xor     ebx, ebx
.input_loop:
    cmp     bl, BYTE [ebp - 4]
    jnl     .end_input_loop

    lea     eax, [ebp - 8]
    push    eax
    push    fmt_in_ch
    call    scanf
    add     esp, 8

    xor     eax, eax
    mov     al, BYTE [ebp - 8]
    sub     al, 0x40
    lea     eax, [edi + 2 * eax + 1]
    push    eax
    dec     eax
    push    eax
    push    fmt_in_ch2
    call    scanf
    add     esp, 12

    inc     ebx
    jmp     .input_loop

.end_input_loop:
    mov     eax, 0x40404040
    movd    xmm1, eax
    pshufd  xmm1, xmm1, 0x00
    mov     edx, DWORD [ebp - 4]
    inc     edx
    test    dl, 7
    setnz   al
    shr     dl, 3
    add     dl, al
    xor     ecx, ecx
.convert_loop:
    cmp     cl, dl
    jnl     .end_convert_loop

    shl     ecx, 1
    movaps  xmm0, [edi + 8 * ecx]
    movaps  xmm2, xmm0
    pcmpgtb xmm2, xmm1
    pand    xmm0, xmm2
    movaps  xmm3, xmm1
    pand    xmm3, xmm2
    psubb   xmm0, xmm3
    movaps  [edi + 8 * ecx], xmm0
    shr     ecx, 1
    inc     ecx
    jmp     .convert_loop

.end_convert_loop:
    mov     esi, outbuf
    push    1
    xor     ecx, ecx
    call    preorder
    xor     ecx, ecx
    call    inorder
    xor     ecx, ecx
    call    postorder

    push    esi
    call    puts
    add     DWORD [esp], 32
    call    puts
    add     DWORD [esp], 32
    call    puts
    add     esp, 8

    xor     eax, eax
    pop     edi
    pop     esi
    pop     ebx
    leave
    ret

preorder:
    push    ebp
    mov     ebp, esp
    mov     eax, DWORD [ebp + 8]
    test    al, al
    jz      .skip_null

    push    ebx
    mov     bx, WORD [edi + 2 * eax]

    add     al, 0x40
    mov     BYTE [esi + 1 * ecx], al
    inc     ecx

    mov     al, bl
    push    eax
    call    preorder

    mov     al, bh
    push    eax
    call    preorder

    add     esp, 8
    pop     ebx

.skip_null:
    leave
    ret

inorder:
    push    ebp
    mov     ebp, esp

    mov     eax, DWORD [ebp + 8]
    test    al, al
    jz      .skip_null

    push    ebx
    mov     bx, WORD [edi + 2 * eax]

    xchg    al, bl
    push    eax
    call    inorder

    xchg    al, bl
    add     al, 0x40
    mov     BYTE [esi + 1 * ecx + 32], al
    inc     ecx

    mov     al, bh
    push    eax
    call    inorder

    add     esp, 8
    pop     ebx

.skip_null:
    leave
    ret

postorder:
    push    ebp
    mov     ebp, esp

    mov     eax, DWORD [ebp + 8]
    test    al, al
    jz      .skip_null

    push    ebx
    mov     bl, al
    shl     ebx, 16
    mov     bx, WORD [edi + 2 * eax]

    mov     al, bl
    push    eax
    call    postorder

    mov     al, bh
    push    eax
    call    postorder

    shr     ebx, 16
    mov     al, bl
    add     al, 0x40
    mov     BYTE [esi + 1 * ecx + 64], al
    inc     ecx

    add     esp, 8
    pop     ebx

.skip_null:
    leave
    ret
