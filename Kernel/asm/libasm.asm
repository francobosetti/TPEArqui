GLOBAL cpuVendor

GLOBAL getSeconds
GLOBAL getMins
GLOBAL getHour
GLOBAL getKey
GLOBAL getDayOfMonth
GLOBAL getMonth
GLOBAL getYear

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid

	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

%macro getClock 1
	push rbp
    mov rbp, rsp

    mov al, %1
    out 70h, al
    in al, 71h

    leave
    ret
%endmacro

getSeconds:
    getClock 0

getMins:
    getClock 2

getHour:
    getClock 4

getDayOfMonth:
    getClock 7

getMonth:
    getClock 8

getYear:
    getClock 9


getKey:
    push rbp
    mov rbp, rsp
    mov rax,0

.loop:
    in al,0x64
    and al,0x01
    cmp al, 0
    je .loop
    in al,0x60

    mov rsp, rbp
    pop rbp
    ret

