#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

#define TRUE 1
#define FALSE !TRUE

enum fds{STDIN=0, STDOUT, STDERR, STDDER, STDIZQ, STDBOTH, STDERRDER, STDERRIZQ, STDERRBOTH};
enum tasks{firstTask = 0, secondTask};

#define STOP_FIRST '1'
#define STOP_SECOND '2'
#define EXIT_KEY 27

void addTask(void * str, uint8_t flag);
void removeTask(uint8_t task);
uint8_t removeCurrentTask();
void runCurrentTask();
void runTasks();
uint8_t getCantTasks();

#endif //SCHEDULER_H
