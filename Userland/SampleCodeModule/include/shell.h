#ifndef SAMPLECODEMODULE_SHELL_H
#define SAMPLECODEMODULE_SHELL_H

#include <stdint.h>

typedef void (*commandPointer)(void);
typedef void (*parallelPointer)(uint8_t fd);

void stopForCommand();
int execute(char * command);

#endif //SAMPLECODEMODULE_SHELL_H

