#include "shell.h"
#include "library.h"
#include "clock.h"
#include "help.h"
#include "fibonacci.h"
#include "primeNums.h"
#include "exceptionTester.h"

#define MAX_LEN_COMMAND 128
#define NUM_COMMANDS 6
#define NUM_LOOP_COMMANDS 2

//defino una memoria auxiliar para mi vector de strings
#define AUXVECTORLENGTH 20

typedef struct{
    char * name;
    parallelPointer parallelismFunction;
    commandPointer function;
}command;

static command availableCommands[NUM_COMMANDS] = {{"help", NULL, &help},
                                   { "divZero", NULL, &divideZero},
                                   { "invalidOpCode", NULL, &invalidOpCode},
                                   {"inforeg",NULL, &infoReg},
                                   {"printmem",NULL, &printMem},
                                   {"time", NULL, &time},
                                   };

static command loopCommands[NUM_LOOP_COMMANDS]= {{"primos", &nextPrime, &primeNumbers},
                                                {"fibonacci", &nextFibo, &fibo}};


// funcion para parsear el string, cada fila de la matriz es un string
//devuelve cantidad de palabras (incluyendo el pipe) que encontro
int parseString(char m[][MAX_LEN_COMMAND], char * src) {
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
    /*
    if(stringsDim==1){
        if(!addFunction(strings[0])){
            printErr(strings[0]);
            printErr(" : comando no encontrado\n");
        }

    }else if(stringsDim==2){

        if(!addFunction(strings[0])){
            printErr(strings[0]);
            printErr(" : comando no encontrado\n");
        }


    }else if(stringsDim==3){                 //pipe de dos funciones sin args
        if(strcmp(strings[1],'|') == 0){
            if(!addFunction(strings[0])){
                printErr(strings[0]);
                printErr(" : comando no encontrado\n");
            }
            if(!addFunction(strings[2])){
                printErr(strings[2]);
                printErr(" : comando no encontrado\n");
            }
        } else{
            printErr("Combinacion de argumentos no valida\n");
        }

    }else if(stringsDim==4){
        if(strcmp)
    }
    else if(stringsDim==5){

    }
    else{
        printErr("Combinacion de argumentos no valida\n");
    }
     */

    
    if(!execute(currentLine)){
        printErr(currentLine);
        printErr(" : comando no encontrado\n");
    }
    printk("\n");
}

int addFunction(char * command){

    for(int i=0 ; i < NUM_LOOP_COMMANDS; ++i){
        if(strcmp(command,loopCommands[i].name) == 0){
            sysTask(loopCommands[i].function());
            return TRUE;
        }
    }

    return FALSE;
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