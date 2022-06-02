#include "include/primeNums.h"
#include "include/library.h"
#include <stdint.h>

static uint64_t current = 2;

int isPrime(uint64_t number) {
    for (uint64_t i=2; i<number/2; i++) {
        if (number % i == 0 && i != number)
            return 0;
    }
    return 1;
}

void nextPrime(uint8_t fd){
    if(current == 2)
        printkfd(fd, "Prime Numbers: \n");
    if(isPrime(current))
        printkfd(fd, "%d\n", current);
    current++;
}

void primeNumbers(){
    /* Find all Prime numbers between 1 to end */
    while (1)
        nextPrime(STDOUT);
}

void restartPrimes(){
    current=2;
}
