#include <stdio.h>
#include <stdlib.h>
#include "shellprinting.h"
#define true 1
#define INT_MAX 2147483647
char * username ;
char * homedir ;
void * printSchemeToscreen(){
    changeColor(YELLOW);
    printf("(%s)",username);
    changeColor(PURPLE);
    printf("@");
    changeColor(GREEN);
    printf("[%s]",homedir);
    changeColor(RED);
    printf(":>>");
    changeColor(DEFAULTCOLOR);

}




int main() {
   username= getenv("USER");
   homedir = getenv("HOME");
    while(true){
    printSchemeToscreen();
    char command[2048] ;
    char * a = input(printSchemeToscreen);
    printf(a);

    break ;



    }

    return 0;
}
