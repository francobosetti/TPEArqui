#include "naiveConsole.h"
#include "stdint.h"
#include "lib.h"
#include "keyboard.h"
#include "scheduler.h"
#include "interrupts.h"

typedef void (*Exception)(void);

static void zeroDivision();
static void invalidOpcode();

char* regNameArr[]={"RAX: ", "RBX: ", "RCX: ", "RDX: ", "RBP: ", "RSI: ", "RDI: ", "RSP: ", "R8:  ","R9:  ","R10: ","R11: ","R12: ","R13: ","R14: ","R15: "};

static Exception exceptions[]={&zeroDivision, 0, 0, 0, 0, 0, &invalidOpcode};

void exceptionHandler(char * errMsg){
    uint8_t taskRemoved = removeCurrentTask();
    uint64_t * regArr= prepareRegisters();
    uint8_t fd = STDERR;
    char * message = "Ingrese ESC para reiniciar SHELL";

    if(getTwoTaskFlag()){
        if(taskRemoved == firstTask)
            fd=STDERRIZQ;
        else if (taskRemoved == secondTask)
            fd=STDERRDER;
    }

    ncClearFd(fd);
    ncPrintFdAttribute(fd, errMsg, Red, Black);
    ncNewLineFd(fd);
    for (int i = 0; i < 16; ++i) {
        ncPrintFdAttribute(fd, regNameArr[i], Red, Black);
        ncPrintHexFdAttribute(fd, regArr[i], Red, Black);
        ncNewLineFd(fd);
    }
    ncPrintFdAttribute(fd, message, Red, Black);
    ncNewLineFd(fd);

    if(getCantTasks()!=0)
        runTasks();
    else{
        _sti();
        do{
            _hlt();//hlt frena el CPU hasta que se detecte la proxima interrupcion externa
        }while((getCharKernel()) != EXIT_KEY);
        ncClear();
        ncNewline();
        resetScheduler();
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