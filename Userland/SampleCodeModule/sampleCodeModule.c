#include "library.h"
#include "shell.h"
#include "help.h"

#define TRUE 1
#define FALSE !TRUE

static int firstEntry = TRUE;

int main() {
    if(firstEntry){
        printk("Lettuce OS shell\n\n");
        help(STDOUT);
    }

    while (firstEntry && getChar() != '\n')
        ;

    firstEntry = FALSE;

    while (1){
        printk("> ");
        stopForCommand();
    }

    return 0;
}