#include <stdio.h>
#include <stdlib.h>
#include "shellprinting.h"
#include "DataStructers/linkedList.h"

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

void print(void * param){
    int * pr = param ;
    printf("%d\n",*pr);
    fflush(stdout);
}


int main() {

    char * a = "idan\0";
    for(int i=0 ;i < 251;i++) {
        changeColor(i);
        printf("%d is idan\n",i);
    }

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
