#include "inforeg.h"
#include "sysCalls.h"
#include "library.h"

#define DISTANCE_TO_ERRORFD 3

static char* regNameArr[]={"RAX: ", "RBX: ", "RCX: ", "RDX: ", "RBP: ", "RSI: ", "RDI: ", "RSP: ", "R8:  ","R9:  ","R10: ","R11: ","R12: ","R13: ","R14: ","R15: "};

void infoReg(uint8_t fd){
    uint64_t buff[CANT_REGS];

    if(sysInfoReg(buff) !=  -1){
        for ( int i = 0; i < CANT_REGS ; i++){
            printkfd(fd, "%s%x\n", regNameArr[i] ,buff[i]);
        }
    }
    else{
        if(fd  == STDOUT)
            fd = STDERR;
        else
            fd += DISTANCE_TO_ERRORFD;

        printkfd(fd, "El guardado de registros no fue inicializado, presione CTRL.\n");
    }
}
