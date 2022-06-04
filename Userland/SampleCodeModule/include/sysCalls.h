#ifndef SAMPLECODEMODULE_SYSCALLS_H
#define SAMPLECODEMODULE_SYSCALLS_H

#include "clock.h"
#include "shell.h"
#include <stdint.h>

int sysWrite(uint64_t fd,const char *c, uint64_t length);
int sysRead(uint64_t fd,const char *c, uint64_t length);
void sysTime(clock * cptr);
int sysInfoReg(uint64_t * regs);
int sysPrintMem(uint8_t * mem, uint64_t address);
void sysSleep(uint64_t secs);
void sysClearScreen();
void sysOneTask(void * str, uint8_t flag);
void sysTwoTasks(void * str1, uint8_t flag1, void * str2, uint8_t flag2);

#endif //SAMPLECODEMODULE_SYSCALLS_H
