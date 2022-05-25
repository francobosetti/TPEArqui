#include <stdint.h>
#include "include/clock.h"
#include "include/sysCalls.h"
#include "include/library.h"

void time(){
    clock time;//todo revisar si esto deberia ser un puntero o no
    sysTime(&time);
    printk("La hora del sistema es: %d:%d:%d %d/%d/%d\n", time.hours, time.minutes, time.seconds, time.dayOfMonth, time.month, time.year);

}