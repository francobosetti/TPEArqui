#ifndef SAMPLECODEMODULE_SYSCALLS_H
#define SAMPLECODEMODULE_SYSCALLS_H

#include "clock.h"
#include <stdint.h>
void write(uint64_t fd,const uint8_t *c, uint64_t length);
void sysTime(clock * cptr);

#endif //SAMPLECODEMODULE_SYSCALLS_H
