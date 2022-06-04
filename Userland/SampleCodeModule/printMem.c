#include "printMem.h"
#include "library.h"
#include "sysCalls.h"
#include <stdint.h>

#define BUFFSIZE 128



/*
 while((c=get_char()) != '\n' && counter < 32){
    if(( c >= '0' && c <= '9')) {
       num[counter++] = (c - '0');
    }
    else if(( c >= 'A' ) && ( c <= 'F' )) {
       num[counter++] = (c - 'A' + 10);
    }
    else if(( c >= 'a') && ( c <= 'f')) {
        num[counter++] = (c - 'a' + 10);
    }
    else if(c == '\b') {
      if(counter > 0){
        put_char(STDOUT, c);
        num[--counter] = 0;
      }
    }
    else {
      num[counter++] = 16 + c;
    }
    if(c != '\b'){
      put_char(STDOUT, c);
    }
 */



#define BITMAX 64
/*
uint64_t stringToHexa(char * buff){

    //sumo 2 a bitMax considerando el 0x......
    for ( int i = 0; buff[i] && i < BITMAX + 2; i++){
            char c = buff[i];
        if(( c >= '0' && c <= '9')) {
            num[counter++] = (c - '0');
        }
        else if(( c >= 'A' ) && ( c <= 'F' )) {
            num[counter++] = (c - 'A' + 10);
        }
        else if(( c >= 'a') && ( c <= 'f')) {
            num[counter++] = (c - 'a' + 10);
        }
        else if(c == '\b') {
            if(counter > 0){
                put_char(STDOUT, c);
                num[--counter] = 0;
            }
        }
        else {
            num[counter++] = 16 + c;
        }
        if(c != '\b'){
            put_char(STDOUT, c);
        }
        }
}*/


void printMem(char * str, uint8_t fd){
    uint64_t address;
    int len = getStringLength(str);
    //chequeo si address cumple con 0x12345678h (0x[0-9a-f]{8}h)??
    if ( len<3 || len >11 || str[0]!='0' || str[1]!='x'){
        printkfd(fd,"Dirección invalida");
        return;
    }
    //transformo el string en hexa a un int para pasarselo a sys_mem
    for(int i=2; i<len; i++){
		if(str[i]>='0' && str[i]<='9')
			address = 16*address + str[i]-'0';
		else if(str[i]>='a' && str[i]<='f')
			address = 16*address + str[i]-'a';
		else{
            printkfd(fd,"Dirección invalida");
            return;
        }
	}

    uint8_t mem[BUFFSIZE];
    printkfd(fd, "%d\n", address);
    int retval = sysPrintMem(mem, address);
    if(retval==-1){
        printkfd(fd, "Direccion invalida\n");
    }else{
        for(int t=0; t<32; t++) {
            printkfd(fd,"Posicion(%d) = %x\n", t, (int) mem[t]);
        }
        printkfd(fd,"\n");
    }
}

