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
    ncPrintAttribute(errMsg, Red, Black); //TODO Revisar como queremos hacer que imprima la salida de error
    ncNewline();
    //TODO poner la funcion que imprime los estados de registros
    uint64_t * regArr= prepareRegisters();
    for (int i = 0; i < 16; ++i) {
        ncPrint(regNameArr[i]);
        ncPrintHex(regArr[i]);
        ncNewline();
    }
    ncNewline();
    //Seccion de frenado de Procesos
    ncPrintAttribute("Ingrese ESC para reiniciar SHELL", Red, Black);

    removeCurrentTask();
    runTasks();
    //aca hay que volver a darle el control al usuario
    
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