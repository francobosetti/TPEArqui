#include "scheduler.h"
#include "keyboard.h"

#define STOP_FIRST 1
#define STOP_SECOND 2

#define NULL (void *) 0
#define MAX_TASKS 2

static taskPointer tasks[MAX_TASKS];
static uint8_t cantTasks = 0;
static uint8_t currentTask = 0;
static uint8_t duplicatedTask = FALSE;

static void * const sampleCodeModuleAddress = (void*)0x400000;
typedef int (*EntryPoint)();

void addTask(taskPointer function){
    if(cantTasks >= MAX_TASKS)
        return;

    tasks[cantTasks++] = function;
    if(tasks[cantTasks-1] == function)
        duplicatedTask = TRUE;
}

void removeTask(uint8_t task){
    if(task<=0 || task > MAX_TASKS)
        return;
    tasks[task-1] = NULL;
    duplicatedTask = FALSE;
}

void removeCurrentTask(){
    if(cantTasks == 0)
        return;
    tasks[currentTask] = NULL;
    cantTasks--;
    duplicatedTask = FALSE;
}

void runCurrentTask(){
    uint8_t fd = STDOUT;
    if(tasks[currentTask] != NULL && cantTasks >  1){
        if(duplicatedTask)
            fd = STDBOTH;
        else if(currentTask == 0)
            fd = STDIZQ;
        else
            fd = STDDER;
    }
    tasks[currentTask](fd);
}

void runTasks(){
    uint8_t c;
    while (cantTasks > 0 && (c = getCharKernel()) != EXIT_KEY){

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
    ((EntryPoint)sampleCodeModuleAddress)();
}




