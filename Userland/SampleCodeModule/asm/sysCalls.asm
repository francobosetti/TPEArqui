GLOBAL sysWrite
GLOBAL sysRead
GLOBAL sysTime
GLOBAL sysClearScreen
GLOBAL sysPrintMem
GLOBAL sysInfoReg
GLOBAL sysHasTicked
GLOBAL sysOneTask
GLOBAL sysTwoTasks

section .data
    SYSREAD equ 0
    SYSWRITE equ 1
    SYSCLEARSCREEN equ 69
    SYSPRINTMEM equ 70
    SYSINFOREG equ 71
    SYSHASTICKED equ 72
    SYSONETASK equ 73
    SYSTWOTASKS equ 74
    SYSTIME equ 201

section .text

; uso esta syscall para imprimir caracter en pantalla, aparece con sys

sysWrite:
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

sysRead:
    push rbp
    mov rbp, rsp
    mov rax, SYSREAD

        ;en rdi tengo el fileDescriptor ya
        ;en rsi tengo el puntero al caracter
        ;en rdx tengo la longitud
    int 80h
    ;tengo en rax, el valor de retorno de la interrupcion
    mov rsp, rbp
    pop rbp
    
    ret

sysTime:
    push rbp
    mov rbp, rsp
    mov rax, SYSTIME
    ;ya tengo en rdi el puntero a la estructura
    ; TODO CHEQUEAR SI SYSCALL RECIBE CORRECTAMENTE EL PUNTERO DEL CLOCK
    int 80h
    mov rsp, rbp
    pop rbp
    ret

sysClearScreen:
    push rbp
    mov rbp, rsp
    mov rax, SYSCLEARSCREEN

    int 80h
    mov rsp, rbp
    pop rbp
    ret

 sysInfoReg:
    push rbp
    mov rbp, rsp
    mov rax, SYSINFOREG

    int 80h
    mov rsp, rbp
    pop rbp
    ret

  sysPrintMem:
      push rbp
      mov rbp, rsp
      mov rax, SYSPRINTMEM

          ;en rdi tengo la direccion de mem, en rsi address

      int 80h
      mov rsp, rbp
      pop rbp
      ret

sysHasTicked:
    push rbp
    mov rbp, rsp
    mov rax, SYSHASTICKED

    int 80h
    mov rsp, rbp
    pop rbp
    ret

sysOneTask:
    push rbp
    mov rbp, rsp
    mov rax, SYSONETASK
    ;en rdi ya tengo el puntero a la task
    ;en rsi tengo el tipo de dato, 1 si con arg no ciclica,

    int 80h
    mov rsp, rbp
    pop rbp
    ret


sysTwoTasks:
    push rbp
    mov rbp, rsp
    mov rax, SYSTWOTASKS

    int 80h
    mov rsp, rbp
    pop rbp
    ret
