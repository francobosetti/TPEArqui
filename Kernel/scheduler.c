#include "scheduler.h"
#include "keyboard.h"
#include "naiveConsole.h"
#include "lib.h"

#define STOP_FIRST 1
#define STOP_SECOND 2

#define NULL (void *) 0
#define MAX_TASKS 2

#define NO_ARG_TASK 1
typedef void (*noArgPointer)(uint8_t fd);
typedef struct{
    noArgPointer function;
    uint8_t isLoop;
}noArgTask;

#define ARG_TASK 2
typedef void (*argPointer)(char * arg, uint8_t fd);
typedef struct{
    argPointer function;
    char * arg1;
}argTask;

static int cantTasks = 0;
static int currentTask = 0;
static int duplicatedTask = FALSE;

static noArgTask * noArgTasks[MAX_TASKS] = {NULL, NULL};
static argTask * argTasks[MAX_TASKS] = {NULL, NULL};
static int fds[MAX_TASKS];


void setFds(){
    for (int i = 0, fd; i < MAX_TASKS; ++i) {
        fd = STDOUT;
        if(cantTasks>1){
            if(duplicatedTask)
                fd = STDBOTH;
            else if(i == 0)
                fd = STDIZQ;
            else
                fd = STDDER;
        }
        fds[i] = fd;
    }
}

int isDuplicatedNoArg(){
    return cantTasks > 1 && (noArgTasks[cantTasks-1]->function == noArgTasks[cantTasks]->function);
}

int isDuplicatedArg(){
    return cantTasks > 1 && (argTasks[cantTasks-1]->function == argTasks[cantTasks]->function);
}

void addTask(void * str, uint8_t flag){
    if(cantTasks >= MAX_TASKS ||  str == NULL)
        return;

   if(flag == NO_ARG_TASK){
       noArgTasks[cantTasks++] = (noArgTask *) str;
       if(isDuplicatedNoArg())
           duplicatedTask=TRUE;
   }
   else if(flag == ARG_TASK){
       argTasks[cantTasks++] = (argTask *) str;
       if(isDuplicatedArg())
           duplicatedTask=TRUE;
   }
}

void removeTask(uint8_t task){
    if(task<=0 || task > MAX_TASKS)
        return;
    noArgTasks[task-1] = NULL;
    argTasks[task-1] = NULL;
    //setFds();
}

uint8_t removeCurrentTask(){
    if(cantTasks == 0)
        return -1;
    noArgTasks[currentTask] = NULL;
    argTasks[currentTask] = NULL;
    cantTasks--;
    //setFds();

    return currentTask;
}

void runCurrentTask(){
    if(cantTasks>0){
        if(noArgTasks[currentTask] != NULL){
            noArgTasks[currentTask]->function(fds[currentTask]);
            if(!noArgTasks[currentTask]->isLoop)
                removeCurrentTask();
        }
        else if(argTasks[currentTask]!=NULL){
            char * arg1 = argTasks[currentTask]->arg1;
            argTasks[currentTask]->function(arg1,fds[currentTask]);
        }
    }
}

void resetScheduler(){
    for (int i = 0; i < MAX_TASKS; ++i) {
        noArgTasks[i] = NULL;
        argTasks[i] = NULL;
    }
    cantTasks=currentTask=0;
    duplicatedTask=FALSE;
}

uint8_t getCantTasks(){
    return cantTasks;
}

/*
int checkNull(){
    return !(argTasks[0]==NULL && argTasks[1]==NULL) || !(noArgTasks[0]==NULL && noArgTasks[1]==NULL);
}*/

void runTasks(){
    char c = 0;
    setFds();
    while (cantTasks > 0/*&& (c = getCharKernel()) != EXIT_KEY*/){
        if(c == STOP_FIRST)
            removeTask(STOP_FIRST);
        else if(c == STOP_SECOND)
            removeTask(STOP_SECOND);

        while(currentTask < MAX_TASKS){
            runCurrentTask();
            currentTask++;
        }

        currentTask = 0;
    }
    resetScheduler();
    give_control_to_user();
}




