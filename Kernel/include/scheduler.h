#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

#define TRUE 1
#define FALSE !TRUE

enum tasks{firstTask = 0, secondTask};
enum stopKeys{STOP_ALL = 27, STOP_FIRST='1', STOP_SECOND='2'};

void addTask(void * str, uint8_t flag);
void removeTask(uint8_t task);
uint8_t removeCurrentTask();
void runCurrentTask();
void runTasks();
void resetScheduler();
uint8_t getTwoTaskFlag();
uint8_t getCantTasks();
void setStopFlag(uint8_t flag);
uint8_t getStopAllFlag();

#endif //SCHEDULER_H
