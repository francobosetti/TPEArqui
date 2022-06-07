#include "registers.h"
#include "scheduler.h"

static uint8_t saved=FALSE;
static uint64_t * regArr;

void saveRegisters(uint64_t * regs){
    regArr=regs;
    saved=TRUE;
}

int getRegisters(uint64_t * regs){
    if(saved){
        //hago una copia de los elementos al vector que me paso el usuario
        for ( int i = 0 ; i < CANT_REGS ; i++) {
            regs[i] = regArr[i];
        }
        return 0;
    }
    return -1;
}
