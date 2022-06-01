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

#define EXIT_KEY 28 //ASCII para la tecla de ESC

typedef void (*taskPointer)(uint8_t fd);

void addTask(taskPointer function);
void removeTask(uint8_t task);
void removeCurrentTask();
void runCurrentTask();
void runTasks();

#endif //SCHEDULER_H
