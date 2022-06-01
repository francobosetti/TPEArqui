#ifndef SAMPLECODEMODULE_SYSCALLS_H
#define SAMPLECODEMODULE_SYSCALLS_H

#include "clock.h"
#include "shell.h"
#include <stdint.h>
int sysWrite(uint64_t fd,const char *c, uint64_t length);
int sysRead(uint64_t fd,const char *c, uint64_t length);
void sysTime(clock * cptr);
void sysInfoReg();
void sysPrintMem(uint64_t * mem, uint64_t address);
void sysHasTicked();
void sysClearScreen();
void sysTask(commandPointer pointer);
void sysRunTasks();

#endif //SAMPLECODEMODULE_SYSCALLS_H
