#ifndef SAMPLECODEMODULE_LIBRARY_H
#define SAMPLECODEMODULE_LIBRARY_H

#include <stdarg.h>
#include <stdint.h>


void printString(uint64_t fd, const uint8_t * vec);
void putCharacter(uint64_t fd, uint8_t c);
void vprintk(uint64_t fd,const uint8_t * fmt, va_list args);
void printk(const uint8_t * fmt, ...);

#endif //SAMPLECODEMODULE_LIBRARY_H
