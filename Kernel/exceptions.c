#include "naiveConsole.h"

#define ZERO_EXCEPTION_ID 0
#define INVALID_OPCODE 6


static void zeroDivision() {
    char * errMsg= "Error: Program tried to devide by zero. Stopping process.";
    ncPrintAtribute(errMsg, Red, Black); //TODO Revisar como queremos hacer que imprima la salida de error

	// Handler para manejar excepcíon
    //TODO aca poner la funcion que imprime los estados de registros
}

static void invalidOpcode() {
    char * errMsg= "Error: Invalid operation code. Stopping process.";
    ncPrintAtribute(errMsg, Red, Black); //TODO Revisar como queremos hacer que imprima la salida de error
    // Handler para manejar excepcíon

    //TODO poner la funcion que imprime los estados de registros
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