#include <stdint.h>
#include "time.h"
#include "sysCalls.h"
#include "lib.h"

typedef struct clock{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t dayOfMonth;
    uint8_t month;
    uint8_t year;
}clock;

void time(){
    clock time;//todo revisar si esto deberia ser un puntero o no
    sysTime(&time);
    printk("La hora del sistema es: %d:%d:%d %d/%d/%d\n", time.hours, time.minutes, time.seconds, time.dayOfMonth, time.month, time.year);

}