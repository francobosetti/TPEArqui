#include <lib.h>
#include <naiveConsole.h>

#define CANT_KEYS 128
#define RELEASE 0x80
#define ENTER 28
#define LSHIFT 0x2A
#define RSHIFT 0x36
#define BACKSPACE 14

#define MAX_BUFF 512

//Tabla para convertir lo que recibe getKey en letra
static char kbd_US [CANT_KEYS] =
        {
                0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
                '\t', /* <-- Tab */
                'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
                0, /* <-- control key */
                'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',  0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0,
                '*',
                0,  /* Alt */
                ' ',  /* Space bar */
                0,  /* Caps lock */
                0,  /* 59 - F1 key ... > */
                0,   0,   0,   0,   0,   0,   0,   0,
                0,  /* < ... F10 */
                0,  /* 69 - Num lock*/
                0,  /* Scroll Lock */
                0,  /* Home key */
                0,  /* Up Arrow */
                0,  /* Page Up */
                '-',
                0,  /* Left Arrow */
                0,
                0,  /* Right Arrow */
                '+',
                0,  /* 79 - End key*/
                0,  /* Down Arrow */
                0,  /* Page Down */
                0,  /* Insert Key */
                0,  /* Delete Key */
                0,   0,   0,
                0,  /* F11 Key */
                0,  /* F12 Key */
                0,  /* All other keys are undefined */
        };

static char shift_kbd_US [CANT_KEYS] =
        {
                0,  27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
                '\t', /* <-- Tab */
                'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
                0, /* <-- control key */
                'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '`',  0, '|',
                'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?',   0,
                '*',
                0,  /* Alt */
                ' ',  /* Space bar */
                0,  /* Caps lock */
                0,  /* 59 - F1 key ... > */
                0,   0,   0,   0,   0,   0,   0,   0,
                0,  /* < ... F10 */
                0,  /* 69 - Num lock*/
                0,  /* Scroll Lock */
                0,  /* Home key */
                0,  /* Up Arrow */
                0,  /* Page Up */
                '-',
                0,  /* Left Arrow */
                0,
                0,  /* Right Arrow */
                '+',
                0,  /* 79 - End key*/
                0,  /* Down Arrow */
                0,  /* Page Down */
                0,  /* Insert Key */
                0,  /* Delete Key */
                0,   0,   0,
                0,  /* F11 Key */
                0,  /* F12 Key */
                0,  /* All other keys are undefined */
        };

char keyboardBuffer[MAX_BUFF];
uint16_t currentPos = 0;

void ncPrintKey(uint16_t code){
    if(code < CANT_KEYS) {
        char toPrint = kbd_US[code];
        if (toPrint != 0)
            ncPrintChar(toPrint);
    }
}

void ncPrintKeyShift(uint16_t code){
    if(code < CANT_KEYS) {
        char toPrint = shift_kbd_US[code];
        if (toPrint != 0)
            ncPrintChar(toPrint);
    }
}

static uint8_t shiftFlag = 0;
void keyboard_handler(){
    uint16_t teclahex = getKey();

    if(teclahex == RSHIFT || teclahex == LSHIFT)
        shiftFlag = 1;
    else if(teclahex == (RSHIFT + RELEASE) || teclahex == (LSHIFT + RELEASE)) //Ambos release shifts del teclado
        shiftFlag = 0;
    else if(teclahex == ENTER){
        ncNewline();
        currentPos = 0;
    }
    else if(teclahex == BACKSPACE){ //TODO:Chequear si borra mas alla de la linea del shell
        if(currentPos>0){
            ncDeleteChar();
            currentPos--;
        }
    }
    else if(shiftFlag == 0){
        ncPrintKey(teclahex);
        keyboardBuffer[currentPos++] = kbd_US[teclahex];
    }
    else{
        ncPrintKeyShift(teclahex);
        keyboardBuffer[currentPos++] = shift_kbd_US[teclahex];
    }
}

char * getBuffer(){
    return keyboardBuffer;
}


