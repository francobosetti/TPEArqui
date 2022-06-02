#ifndef PIPE_H
#define PIPE_H

typedef void (*commandPointer)(void);
void pipe(commandPointer f1,char * arg1, commandPointer f2, char * arg2);


#endif //PIPE_H
