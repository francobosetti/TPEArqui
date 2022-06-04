#include "shell.h"
#include "library.h"
#include "clock.h"
#include "help.h"
#include "fibonacci.h"
#include "primeNums.h"
#include "exceptionTester.h"
#include "printMem.h"
#include "sysCalls.h"

#define MAX_LEN_COMMAND 128
#define AUXVECTORLENGTH 20
#define MAXCOMMANDS 2

#define PIPE "|"

typedef struct{
    char * name;
    noArgPointer function;
}noArgCommand;

typedef struct{
    char * name;
    argPointer function;
}argCommand;


#define NUM_COMMANDS_NO_ARG 5
static noArgCommand noArgumentCommands[NUM_COMMANDS_NO_ARG] = {{"help", &help},
                                   { "divZero", &divideZero},
                                   { "invalidOpCode", &invalidOpCode},
                                   //{"inforeg", &infoReg},
                                   {"time", &time},
                                   };

#define NUM_LOOP_COMMANDS 2
static noArgCommand loopCommands[NUM_LOOP_COMMANDS]= {{"primos", &nextPrime},
                                                      {"fibonacci", &nextFibo}};

#define NUM_COMMANDS_ARG 1
static argCommand argumentCommands[NUM_COMMANDS_ARG] = {{"printmem", &printMem}};



enum inputCases{SINGLE_FUNCTION = 1, SINGLE_FUNC_W_ARG, PIPE_NO_ARGS, PIPE_ONE_ARG, PIPE_TWO_ARGS};

#define CANT_ERR_MESSAGES 3
char * errMessages[CANT_ERR_MESSAGES] = {" : comando no encontrado\n",
                                        "Combinacion de argumentos no valida\n",
                                        " : comando no encontrado/ Combinacion invalida de argumentos\n"};

static argTask * arrArgTask[MAXCOMMANDS]={NULL, NULL};
static noArgTask * arrNoArgTask[MAXCOMMANDS]={NULL, NULL};
static int numCommands=0;

// funcion para parsear el string, cada fila de la matriz es un string
//devuelve cantidad de palabras (incluyendo el pipe) que encontro
int parseString(char m[][MAX_LEN_COMMAND], const char * src) {
    int dim = 0;
    int j = 0;
    int i = 0;

    //salteo los primeros  espacios
    while ( src[i] == ' ')
        i++;

    while ( src[i] != 0)
    {
        if ( src[i] != ' '){
            m[dim][j++] = src[i];
            //si estoy terminando el string!
            if ( src[i + 1] == 0){
                m[dim][j] = 0;
                dim++;
            }
            i++;
        } else {
            //completo String anterior
            m[dim][j] = 0;
            while ( src[i] == ' ')
                i++;
            //aumento dimension de la matriz
            dim++;
            j = 0;
        }
    }
    return dim;
}

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

    //probaciones
    char strings[AUXVECTORLENGTH][MAX_LEN_COMMAND];
    int stringsDim = parseString(strings , currentLine);
    char errFlag = FALSE;
    argTask argTask1, argTask2;
    noArgTask noArgTask1, noArgTask2;

    switch (stringsDim) {
        case SINGLE_FUNCTION:
            if(!addFunction(&noArgTask1,strings[0]) && !execute(&noArgTask1,strings[0])){
                printErr(strings[0]);
                printErr(errMessages[0]);
                errFlag=TRUE;
            }
            break;
        case SINGLE_FUNC_W_ARG:
            if(!executeArgument(&argTask1,strings[0],strings[1])){
                printErr(strings[0]);
                printErr(errMessages[2]);
                errFlag=TRUE;
            }
            break;
        case PIPE_NO_ARGS:
            if(strcmp(strings[1],PIPE) == 0){
                sysClearScreen();
                if(!addFunction(&noArgTask1,strings[0]) && !execute(&noArgTask1,strings[0])){
                    printkfd(STDERRIZQ, strings[0]);
                    printkfd(STDERRIZQ, errMessages[0]);
                    errFlag=TRUE;
                }
                if(!addFunction(&noArgTask2,strings[2]) && !execute(&noArgTask2,strings[2])){
                    printkfd(STDERRDER, strings[2]);
                    printkfd(STDERRDER, errMessages[0]);
                    errFlag=TRUE;
                }
            } else{
                printErr(errMessages[1]);
                errFlag=TRUE;
            }
            break;
        case PIPE_ONE_ARG:
            if(strcmp(strings[1],PIPE) == 0){
                sysClearScreen();
                if(!addFunction(&noArgTask1,strings[0]) && !execute(&noArgTask1,strings[0])){
                    printkfd(STDERRIZQ, strings[0]);
                    printkfd(STDERRIZQ, errMessages[0]);
                    errFlag=TRUE;
                }
                if(!executeArgument(&argTask2,strings[2],strings[3])){
                    printkfd(STDERRDER, strings[2]);
                    printkfd(STDERRDER, errMessages[2]);
                    errFlag=TRUE;
                }
            }
            else if(strcmp(strings[2],PIPE) == 0){
                sysClearScreen();
                if(!executeArgument(&argTask1,strings[0],strings[1])){
                    printkfd(STDERRIZQ, strings[0]);
                    printkfd(STDERRIZQ, errMessages[2]);
                    errFlag=TRUE;
                }
                if(!addFunction(&noArgTask2,strings[3]) && !execute(&noArgTask2,strings[3])){
                    printkfd(STDERRDER, strings[3]);
                    printkfd(STDERRDER, errMessages[0]);
                    errFlag=TRUE;
                }
            }
            else{
                printErr(errMessages[1]);
                errFlag=TRUE;
            }
            break;
        case PIPE_TWO_ARGS:
            if(strcmp(strings[2],PIPE) == 0){
                sysClearScreen();
                if(!executeArgument(&argTask1,strings[0],strings[1])){
                    printkfd(STDERRIZQ, strings[0]);
                    printkfd(STDERRIZQ, errMessages[2]);
                    errFlag=TRUE;
                }
                if(!executeArgument(&argTask2,strings[3],strings[4])){
                    printkfd(STDERRDER, strings[3]);
                    printkfd(STDERRDER, errMessages[2]);
                    errFlag=TRUE;
                }
            } else{
                printErr(errMessages[1]);
                errFlag=TRUE;
            }
            break;
        default:
            printErr(errMessages[1]);
            errFlag=TRUE;
    }
    if(!errFlag){
        switch (numCommands) {
            case 1:
                if(arrNoArgTask[0]!=NULL){
                    //syscall de 1 task con arrNoArgTask[0]
                    sysOneTask(arrNoArgTask[0], NO_ARG_TASK);
                }
                else{
                    //syscall de 1 task con arrArgTask[0]
                    sysOneTask(arrArgTask[0], ARG_TASK);
                }
                break;
            case 2:
                //syscall de 2 tasks
                sysTwoTasks(arrArgTask[0]!=NULL?arrArgTask[0]:arrNoArgTask[0],arrArgTask[0]!=NULL?ARG_TASK:NO_ARG_TASK,arrArgTask[1]!=NULL?arrArgTask[1]:arrNoArgTask[1],arrArgTask[1]!=NULL?ARG_TASK:NO_ARG_TASK);
                break;
        }
    }

    restartStates();
    printk("\n");
}

void restartStates(){
    restartFibo();
    restartPrimes();
    for (int i = 0; i <MAXCOMMANDS ; ++i) {
        arrNoArgTask[i]=NULL;
        arrArgTask[i]=NULL;
    }

    numCommands=0;
}

int addFunction(noArgTask * str, char * command){
    for(int i=0 ; i < NUM_LOOP_COMMANDS; ++i){
        if(strcmp(command,loopCommands[i].name) == 0){
            str->isLoop=TRUE;
            str->function=loopCommands[i].function;
            arrNoArgTask[numCommands++]=str;
            return TRUE;
        }
    }
    return FALSE;
}
int execute(noArgTask * str, char * command){
    for(int i=0 ; i < NUM_COMMANDS_NO_ARG; ++i){
        if(strcmp(command,noArgumentCommands[i].name) == 0){
            str->isLoop=FALSE;
            str->function=noArgumentCommands[i].function;
            arrNoArgTask[numCommands++]=str;
            return TRUE;
        }
    }
    return FALSE;
}

int executeArgument(argTask * str, char * command, char * arg){
    for(int i = 0 ; i < NUM_COMMANDS_ARG; ++i){
        if(strcmp(command,argumentCommands[i].name) == 0){
            str->function=argumentCommands[i].function;
            str->arg1=arg;
            arrArgTask[numCommands++]=str;
            return TRUE;
        }
    }
    return FALSE;
}