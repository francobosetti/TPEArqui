#include "naiveConsole.h"
#include "stdint.h"
#include "lib.h"
#include "keyboard.h"
#include "scheduler.h"
#include "interrupts.h"

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE 6

typedef void (*Exception)(void);

static void zeroDivision();
static void invalidOpcode();

char* regNameArr[]={"RAX: ", "RBX: ", "RCX: ", "RDX: ", "RBP: ", "RSI: ", "RDI: ", "RSP: ", "R8: ","R9: ","R10: ","R11: ","R12: ","R13: ","R14: ","R15: "};

static Exception exceptions[]={&zeroDivision, 0, 0, 0, 0, 0, &invalidOpcode};

void exceptionHandler(char * errMsg){
    uint8_t taskRemoved = removeCurrentTask();
    uint64_t * regArr= prepareRegisters();

    char * message = "Ingrese ESC para reiniciar SHELL";

    if(taskRemoved == 0){
        ncPrintLeftAttribute(errMsg, Red, Black);
        ncNewlineLeft();
        for (int i = 0; i < 16; ++i) {
            ncPrintLeft(regNameArr[i]);
            ncPrintHexLeft(regArr[i]);
            ncNewlineLeft();
        }
        ncPrintLeftAttribute(message, Red, Black);
        ncNewlineLeft();
    }
    else if (taskRemoved == 1){
        ncPrintRightAttribute(errMsg, Red, Black);
        ncNewlineRight();
        for (int i = 0; i < 16; ++i) {
            ncPrintRight(regNameArr[i]);
            ncPrintHexRight(regArr[i]);
            ncNewlineRight();
        }
        ncPrintRightAttribute(message, Red, Black);
        ncNewlineRight();

    }
    else {
        ncPrintAttribute(errMsg, Red, Black);
        ncNewline();
        for (int i = 0; i < 16; ++i) {
            ncPrint(regNameArr[i]);
            ncPrintHex(regArr[i]);
            ncNewline();
        }
        ncPrintAttribute(message, Red, Black);
        ncNewline();
    }

    _sti();
    if(getCantTasks()!=0)
        runTasks();
    else{
        do{
            _hlt();//hlt frena el CPU hasta que se detecte la proxima interrupcion externa
        }while((getCharKernel()) != EXIT_KEY);
        ncClear();
        give_control_to_user();
    }

}

void exceptionDispatcher(int exception) {
    Exception exFunc = exceptions[exception];
	if(exFunc != 0){
		exFunc();
	}
}

static void zeroDivision() {
    char * errMsg= "Error: Program tried to divide by zero. Stopping process.";
    exceptionHandler(errMsg);
}

static void invalidOpcode() {
    char * errMsg= "Error: Invalid operation code. Stopping process.";
    exceptionHandler(errMsg);
}