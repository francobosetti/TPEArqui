#include "shell.h"
#include "library.h"
#include "clock.h"
#include "help.h"
#include "fibonacci.h"
#include "primeNums.h"
#include "exceptionTester.h"

#define MAX_LEN_COMMAND 128
#define NUM_COMMANDS 6

typedef void (*commandPointer)(void);

typedef struct{
    char * name;
    commandPointer function;
}command;

static command availableCommands[NUM_COMMANDS] = {{"help", &help},
                                   { "divZero", &divideZero},
                                   { "invalidOpCode", &invalidOpCode},
                                   //{&infoReg, "inforeg"},
                                   //{&printMem, "printmem"},
                                   {"time", &time},
                                   {"primos", &primeNumbers},
                                   {"fibonacci", &fibo},
                                   };

void stopForCommand(){
    char c;
    char currentLine[MAX_LEN_COMMAND];
    int i = 0;

    while((c=getChar()) != '\n'){
        if(i>0 && c == '\b'){
            putCharacter(STDOUT, c);
            currentLine[--i] = 0;
        }
        else if(c != '\b') {
            putCharacter(STDOUT, c);
            currentLine[i++] = c;
        }
    }
    printk("\n");
    currentLine[i] = 0;

    if(!execute(currentLine)){
        printErr(currentLine);
        printErr(" : comando no encontrado\n");
    }
}

int execute(char * command){
    for(int i=0 ; i < NUM_COMMANDS; ++i){
        if(strcmp(command,availableCommands[i].name) == 0){
            availableCommands[i].function();
            return TRUE;
        }
    }
    return FALSE;
}