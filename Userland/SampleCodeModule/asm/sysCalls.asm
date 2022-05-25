GLOBAL write
GLOBAL sysTime

section .data
    SYSREAD equ 0
    SYSWRITE equ 1
    SYSCLEARSCREEN equ 69
    SYSTIME equ 201

section .text


; uso esta syscall para imprimir caracter en pantalla, aparece con sys
write:
    push rbp
    mov rbp, rsp
    mov rax, SYSWRITE

    ;en rdi tengo el fileDescriptor ya
    ;en rsi tengo el puntero al caracter
    ;en rdx tengo la longitud

    int 80h
    mov rsp, rbp
    pop rbp
    ret

sysTime:
    push rbp
    mov rbp, rsp
    mov rax, SYSTIME
    ;ya tengo en rdi el puntero a la estructura
    ; TODO CHEQUEAR SI SYSCALL DE TIME SOLO PEDIA PUNTERO A ESTRUCTURA
    int 80h
    mov rsp, rbp
    pop rbp
    ret

