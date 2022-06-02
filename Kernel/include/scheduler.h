#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

#define TRUE 1
#define FALSE !TRUE

#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define STDDER 3
#define STDIZQ 4
#define STDBOTH 5

#define STDERRDER 6
#define STDERRIZQ 7
#define STDERRBOTH 8

#define EXIT_KEY 27

typedef void (*taskPointer)(uint8_t fd);

void addTask(taskPointer function);
void removeTask(uint8_t task);
uint8_t removeCurrentTask();
void runCurrentTask();
void runTasks();

#endif //SCHEDULER_H
