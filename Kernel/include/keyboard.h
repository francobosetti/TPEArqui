#include <stdint.h>

#ifndef KERNEL_KEYBOARD_H
#define KERNEL_KEYBOARD_H

void ncClear();
void keyboard_handler();
//devuelve buffer terminado en \n --> lo vamos a cambiar a string
char * getBuffer();

#endif //KERNEL_KEYBOARD_H
