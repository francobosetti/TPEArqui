#ifndef SAMPLECODEMODULE_SHELL_H
#define SAMPLECODEMODULE_SHELL_H

#include <stdint.h>

typedef void (*noArgPointer)(uint8_t fd);
typedef void (*argPointer)(char * arg, uint8_t fd);

int addFunction(char * command);
void stopForCommand();
int execute(char * command, uint8_t fd);
int executeArgument(char * command, char * arg, uint8_t fd);
int isFunction(char * command);
void restartStates();


#endif //SAMPLECODEMODULE_SHELL_H

