#include <stdio.h>
#include <stdlib.h>
#include "shellprinting.h"
#include "linkedList.h"

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
    int value = 1;
    struct linkedList * test = createLinkedList(sizeof(value));
    pushFront(test,&value);
    value++;
    pushBack(test,&value);
    value++;
    pushBack(test,&value);
    value++;
    pushFront(test,&value);
    forEachLinked(print,test);
printf("part 2 \n ");
    popBack(test);
    popFront(test);
    forEachLinked(print,test);




    return 0;
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
