#include <stdint.h>
#include "naiveConsole.h"
#include "keyboard.h"
#include "lib.h"
#include "time.h"

#define SYS_READ 0
#define SYS_WRITE 1
#define SYS_TIME 201

#define STDOUT 1
#define STDERR 2
#define CANT_GENERAL_REGISTERS 16

//estructura para pasaje de registros


typedef struct registers{
    //array ordenado de la siguiente manera rax, rbx, rcx, rdx, rbp, rsi, rdi, rsp, r8,r9,r10,r11,r12,r13,r14,r15
    //general purpose registers
    uint64_t gpr[CANT_GENERAL_REGISTERS];
    uint64_t rip; //decido separarlo del array porque es un registro distinguido, no es para proposito general
    uint32_t eflags;
} registers;


int sys_read(uint8_t fd, char * buff, uint64_t length){ //TODO: ver tema file descriptor
    if(buff == NULL)
        return 0;

    char * keyboardBuff = getBuffer();
    int i=0;

    while(i < length && keyboardBuff[i] != '\n') {
            buff[i] = keyboardBuff[i];
            i++;
    }
    return i; //returns quantity of bytes read
}

void sys_write(uint8_t fd, char * buff, uint64_t length){
    if(buff == NULL)
        return;

    uint8_t color = White;
    //seteo color rojo en caso de que sea STDERR

    if (fd == STDERR)
        color = Red;

    for (int i = 0; i < length; ++i) {
        ncPrintCharAttribute(buff[i], color, Black);
    }
}

void sys_time(clock * str){
    if(str == NULL)
        return;

    str->seconds = getSeconds();
    str->minutes = getMins();
    str->hours = getHour();
    str->dayOfMonth = getDayOfMonth();
    str->month = getMonth();
    str->year = getYear();
}

void sys_registers(registers * regs){

}

void _int80Dispatcher(uint16_t code, uint64_t arg0, uint64_t arg1, uint64_t arg2) {
    switch (code) {
        case SYS_READ:
            sys_read( (uint8_t) arg0, (char *) arg1, (uint64_t) arg2);
            break;
        case SYS_WRITE:
            sys_write( (uint8_t) arg0, (char *) arg1, (uint64_t) arg2);
            break;
        case SYS_TIME:
            sys_time((clock *) arg0);
            break;
    }
}
