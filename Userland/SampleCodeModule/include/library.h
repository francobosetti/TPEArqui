#ifndef SAMPLECODEMODULE_LIBRARY_H
#define SAMPLECODEMODULE_LIBRARY_H

#include <stdarg.h>
#include <stdint.h>

#define TRUE 1
#define FALSE !TRUE

#define NULL (void *) 0

#define REGULAR 0
#define ESCAPE 1
#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define STDDER 3
#define STDIZQ 4


#define STDBOTH 5
#define STDERRDER 6
#define STDERRIZQ 7
#define STDERRBOTH 8

#define DISTANCE_TO_ERRORFD 3

#define BUFFSIZE 128
#define DECIMALBASE 10
#define HEXABASE 16

void printString(uint64_t fd, const char * vec);
void putCharacter(uint64_t fd, char c);
void vprintk(uint64_t fd,const char * fmt, va_list args);
void printkfd(int fd, const char * fmt, ...);
void printk(const char * fmt, ...);
void printErr(const char * fmt, ...);
int strcmp(const char * str1, const char * str2);
char getChar();
int getStringLength(const char *vec);

#endif //SAMPLECODEMODULE_LIBRARY_H
