#include "library.h"
#include "shell.h"

int main() {

    while (1){
        printk("$ ");
        stopForCommand();
    }
    return 0;
}