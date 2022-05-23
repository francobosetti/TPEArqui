#include "naiveConsole.h"
#include "stdint.h"
#include "lib.h"

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE 6

char* regNameArr[]={"rax: ", "rbx: ", "rcx: ", "rdx: ", "rbp: ", "rsi: ", "rdi: ", "rsp: ", "r8: ","r9: ","r10: ","r11: ","r12: ","r13: ","r14: ","r15: "};

static void zeroDivision() {

    //TODO manejar corte de programa
    char * errMsg= "Error: Program tried to devide by zero. Stopping process.";
    ncPrintAtribute(errMsg, Red, Black); //TODO Revisar como queremos hacer que imprima la salida de error

	// Handler para manejar excepcíon
    //TODO aca poner la funcion que imprime los estados de registros
    uint64_t * regArr= prepareRegisters(); // revisar si esta funcion funciona correctamente

    for (int i = 0; i < 16; ++i) {
        ncPrint(regNameArr[i]);
        ncPrintHex(regArr[i]);
    }
}

static void invalidOpcode() {
    //TODO manejar corte de programa
    char * errMsg= "Error: Invalid operation code. Stopping process.";
    ncPrintAtribute(errMsg, Red, Black); //TODO Revisar como queremos hacer que imprima la salida de error
    // Handler para manejar excepcíon

    //TODO poner la funcion que imprime los estados de registros
    uint64_t * regArr= prepareRegisters();
    for (int i = 0; i < 16; ++i) {
        ncPrint(regNameArr[i]);
        ncPrintHex(regArr[i]);
    }
}

void exceptionDispatcher(int exception) {
    switch (exception) {
        case ZERO_EXCEPTION_ID:
            zeroDivision();
            break;
        case INVALID_OPCODE:
            invalidOpcode();
            break;
    }
}