#ifndef SAMPLECODEMODULE_SYSCALLS_H
#define SAMPLECODEMODULE_SYSCALLS_H

#include "clock.h"
#include <stdint.h>
void sysWrite(uint64_t fd,const char *c, uint64_t length);
void sysRead(uint64_t fd,const char *c, uint64_t length);
void sysTime(clock * cptr);
void sysInfoReg();
void sysPrintMem(uint64_t * mem);
void sysClearScreen();

#endif //SAMPLECODEMODULE_SYSCALLS_H
