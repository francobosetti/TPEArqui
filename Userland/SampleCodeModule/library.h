#ifndef SHELL_C_LIB_H
#define SHELL_C_LIB_H


#endif //SHELL_C_LIB_H

#include <stdarg.h>
#include <stdint.h>


void printString(uint64_t fd, const uint8_t * vec);
void putCharacter(uint64_t fd, uint8_t c);
void vprintk(uint64_t fd,const uint8_t * fmt, va_list args);
extern void write(uint64_t fd,const uint8_t *c, uint64_t length);
void printk(const uint8_t * fmt, ...);

