#include "naiveConsole.h"
#include "stdint.h"
#include "lib.h"
#include "keyboard.h"
#include "scheduler.h"

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
        for (int i = 0; i < 16; ++i) {
            ncPrintLeft(regNameArr[i]);
            ncPrintHexLeft(regArr[i]);
            ncNewlineLeft();
        }
        ncNewlineLeft();
        ncPrintLeftAttribute(message, Red, Black);
    }
    else if (taskRemoved == 1){
        ncPrintRightAttribute(errMsg, Red, Black);
        for (int i = 0; i < 16; ++i) {
            ncPrintRight(regNameArr[i]);
            ncPrintHexRight(regArr[i]);
            ncNewlineRight();
        }
        ncNewlineRight();
        ncPrintRightAttribute(message, Red, Black);

    }
    else {
        ncPrintAttribute(errMsg, Red, Black);
        for (int i = 0; i < 16; ++i) {
            ncPrint(regNameArr[i]);
            ncPrintHex(regArr[i]);
            ncNewline();
        }
        ncNewline();
        ncPrintAttribute(message, Red, Black);
    }

    runTasks();
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