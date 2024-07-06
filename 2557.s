section .data
    msg:    db "Hello World!"

section .text
    global main

main:
    mov eax, 4       ; 
    mov ebx, 1       ; 
    mov ecx, msg     ; 
    mov edx, 12      ; 
    int 0x80         ; 

    mov eax, 0       ; 
    ret              ; 
