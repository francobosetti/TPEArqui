
#include <stdarg.h>
#include <stdint.h>


#define FALSE 0
#define TRUE !FALSE



#define REGULAR 0
#define ESCAPE 1


#define STDOUT 1
#define STDERR 2
#define BUFFSIZE 128

#define DECIMALBASE 10
#define HEXABASE 16


int abs(int num){
    return num >= 0 ? num: -1 * num;
}


// Function to swap two numbers
void swap(uint8_t *x, uint8_t *y) {
    uint8_t t = *x; *x = *y; *y = t;
}

// Function to reverse `buffer[i…j]`
uint8_t* reverse(uint8_t *buffer, int i, int j)
{
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }

    return buffer;
}

// Iterative function to implement `itoa()` function in C
uint8_t* itoa(int value, uint8_t* buffer, int base)
{
    // invalid input
    if (base < 2 || base > 32) {
        return buffer;
    }

    // consider the absolute value of the number
    int n = abs(value);

    int i = 0;
    while (n)
    {
        int r = n % base;

        if (r >= 10) {
            buffer[i++] = 65 + (r - 10);
        }
        else {
            buffer[i++] = 48 + r;
        }

        n = n / base;
    }

    // if the number is 0
    if (i == 0) {
        buffer[i++] = '0';
    }

    // If the base is 10 and the value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base == 10) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0'; // null terminate string

    // reverse the string and return it
    return reverse(buffer, 0, i - 1);
}





void putCharacter(uint64_t fd, uint8_t c){
    write(fd,&c,1);
}


int getStringLength(const uint8_t *vec) {
    int i = 0;
    while ( vec[i] != 0)
        i++;
    return i;
}


void printString(uint64_t fd, const uint8_t * vec){
    int length = getStringLength(vec);
    write(fd,vec,length);
}




void vprintk(uint64_t fd,const uint8_t * fmt, va_list args){
    uint8_t buffer[BUFFSIZE];
    int state = REGULAR;

    while (*fmt) {
        if ( state == REGULAR ){
            if ( *fmt == '%' ){
                state = ESCAPE;
            } else {
                //si estoy en regular y no es caracter especial, entonces lo imprimo
                putCharacter(fd,*fmt);
            }
        } else if ( state == ESCAPE) {
            switch (*fmt)
            {
                case 'c':
                    putCharacter(fd,va_arg(args, int));
                    break;
                case 'd':
                    printString( fd , itoa(va_arg(args,uint32_t),buffer,DECIMALBASE) );
                    break;
                case 'f':
                    break;
                case 's':
                    printString(fd,va_arg(args, const uint8_t *));
                    break;
                case 'x':
                case 'p':
                    putCharacter(STDOUT,'0');
                    putCharacter(STDOUT,'X');
                    printString(fd, itoa( va_arg(args, uint64_t) ,buffer, HEXABASE));
                    break;
                default:
                    break;
            }
            state = REGULAR;
        }
        fmt++;
    }
}


void printk(const uint8_t * fmt, ...){
    va_list args;
    va_start(args,fmt);
    vprintk(STDOUT,fmt,args);
    va_end(args);
}