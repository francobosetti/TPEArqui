#include <stdint.h>

#define NULL (void *) 0
#define MAX_TASKS 2

typedef void (*commandPointer)(void);


static commandPointer tasks[MAX_TASKS];
static uint8_t cantTaks = 0;

void addTask(commandPointer function){
    if(cantTaks >= MAX_TASKS)
        return;
    tasks[cantTaks++] = function;
}

void removeCurrentTask(){
    if(cantTaks == 0)
        return;
    tasks[--cantTaks] = NULL;
}



