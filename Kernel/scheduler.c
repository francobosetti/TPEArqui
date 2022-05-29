#include <stdint.h>
#include "keyboard.h"

#define NULL (void *) 0
#define MAX_TASKS 2

#define STOP_FIRST 1
#define STOP_SECOND 2

#define EXIT_KEY 28 //ASCII para la tecla de ESC

typedef void (*commandPointer)(void);

static commandPointer tasks[MAX_TASKS];
static uint8_t cantTasks = 0;
static uint8_t currentTask = 0;

void addTask(commandPointer function){
    if(cantTaks >= MAX_TASKS)
        return;
    tasks[cantTasks++] = function;
}

void removeTask(uint8_t task){
    if(task<=0 || task > MAX_TASKS)
        return;
    tasks[task-1] = NULL;
}

void removeCurrentTask(){
    if(cantTaks == 0)
        return;
    tasks[currentTask] = NULL;
    cantTasks--;
}

void runCurrentTask(){
    if(tasks[currentTask] != NULL)
        tasks[currentTask](); //TODO ver si aca le pasamos parametro desde kernel o armamos dos wrappers extra en userland
}

void runTasks(){
    uint8_t exit = 0, c;
    while ((c = getCharKernel()) != ESC){

        if(c == STOP_FIRST)
            removeTask(STOP_FIRST);
        else if(c == STOP_SECOND)
            removeTask(STOP_SECOND);

        while(currentTask < cantTasks){
            runCurrentTask();
            currentTask++;
        }

        currentTask = 0;
    }
}




