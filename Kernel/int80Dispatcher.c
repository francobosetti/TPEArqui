#include <stdint.h>
#include "naiveConsole.h"
#include "keyboard.h"
#include "lib.h"
#include "time.h"

#define SYS_READ 0
#define SYS_WRITE 1
//#define SYS_MEM 68
//#define SYS_REGISTERS 69
#define SYS_CLEARSCREEN 69
#define SYS_TIME 201

#define GPRSIZE 16

#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define CANT_GENERAL_REGISTERS 16

#define TRUE 1
#define FALSE !TRUE


extern uint16_t currentPos;
static uint16_t currentCharToRead = 0;

int sys_read(uint8_t fd, char * buff, uint64_t length){ //TODO: ver tema file descriptor
    if(buff == NULL || fd != STDIN || length <= 0 || currentPos == 0)
        return -1;

    char * keyboardBuff = getBuffer();

    int i = 0;
    uint8_t readNewline = FALSE;
    while(i < length && !readNewline) {
            if(keyboardBuff[currentCharToRead] == '\n'){
                readNewline = TRUE;
                buff[i] = keyboardBuff[currentCharToRead]; 
            } else {
                buff[i] = keyboardBuff[currentCharToRead++];
            }
            i++;
    }

    if(keyboardBuff[currentCharToRead] == '\n'){
        currentCharToRead=0;
    }

    return i;
}

int sys_write(uint8_t fd, char * buff, uint64_t length){
    if(buff == NULL)
        return 0;

    uint8_t color = White;
    //seteo color rojo en caso de que sea STDERR
    if (fd == STDERR)
        color = Red;

    int i;
    for (i = 0; i < length; ++i) {
        ncPrintCharAttribute(buff[i], color, Black);
    }
    return i;
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

void sys_clearscreen(){
    ncClear();
}

/*
void sys_registers(uint64_t regs[]){
    //array ordenado de la siguiente manera rax, rbx, rcx, rdx, rbp, rsi, rdi, rsp, r8,r9,r10,r11,r12,r13,r14,r15
    uint64_t *ptr;

    ptr = prepareRegisters();

    for ( int i = 0 ; i < GPRSIZE ; i++){
        //le cargue el valor de los registros
        regs[i] = ptr[i];
    }

}

void sys_mem(uint8_t * mem, uint64_t address){      // cargo en mem 32 bits a partir de address
    for (int i = 0; i < 32; i++) {
        mem[i] = getByte(address);
        address+=8;
    }
}

 */

int _int80Dispatcher(uint16_t code, uint64_t arg0, uint64_t arg1, uint64_t arg2) {
    switch (code) {
        case SYS_READ: //arg0: fd , arg1: buff, arg2: length
            return sys_read( (uint8_t) arg0, (char *) arg1, (uint64_t) arg2);
        case SYS_WRITE: //arg0: fd , arg1: buff, arg2: length
            return sys_write( (uint8_t) arg0, (char *) arg1, (uint64_t) arg2);
        case SYS_TIME: //arg0: clock * donde va a guardar la info
            sys_time((clock *) arg0);
            break;
        case SYS_CLEARSCREEN:
            sys_clearscreen();
            break;

        /*case SYS_MEM:  //arg0: uint8_t * mem, array de 32 lugares de 8bits, arg1: uint64_t address, direc para buscar
            sys_mem((uint8_t *) arg0, (uint64_t) arg1); //todo revisar el tema de que si va en userLand o en KS
            break;
        case SYS_REGISTERS: //arg0: registers * , struct donde va a guardar la info a devolver
            sys_registers((registers *) arg0);
            break;*/

    }
    return 0;
}
