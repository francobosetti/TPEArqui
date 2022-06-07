#ifndef KERNEL_REGISTERS_H
#define KERNEL_REGISTERS_H

#include <stdint.h>

#define CANT_REGS 17

void saveRegisters(uint64_t * regs);
int getRegisters(uint64_t * regs);

#endif //KERNEL_REGISTERS_H
