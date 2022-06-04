#ifndef KERNEL_REGISTERS_H
#define KERNEL_REGISTERS_H

#include <stdint.h>

#define CANT_REGS 16
void saveRegisters();
int getRegisters(uint64_t * regs);

#endif //KERNEL_REGISTERS_H
