#ifndef SAMPLECODEMODULE_SHELL_H
#define SAMPLECODEMODULE_SHELL_H

#include <stdint.h>

typedef void (*noArgPointer)(uint8_t fd);
typedef void (*argPointer)(char * arg, uint8_t fd);

#define NO_ARG_TASK 1
typedef struct{
    noArgPointer function;
    uint8_t isLoop;
}noArgTask;

#define ARG_TASK 2
typedef struct{
    argPointer function;
    char * arg1;
}argTask;


void stopForCommand();
void restartStates();
int execute(noArgTask * str, char * command);
int executeArgument(argTask * str, char * command, char * arg);
int addFunction(noArgTask * str, char * command);



#endif //SAMPLECODEMODULE_SHELL_H

