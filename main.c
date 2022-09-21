#include <stdio.h>
#include <stdlib.h>
#include "shellprinting.h"
#include "DataStructers/linkedList.h"
#include "shellCore.h"
#define true 1
#define INT_MAX 2147483647
char * username ;
char * homedir ;
struct trie * myCommnads;
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

void printStr(void * a){
    struct str * st2 =a ;
    printf("cool : %s \n",st2->vec->arr);
    fflush(stdout);
}

void printAll(void * key , void  * data, size_t len ){
   struct command_shell * tmp = data;
   printf("\ntype : %d color : %d , basePath: %s \n" ,tmp->type ,tmp->colorShow , ((char * ) tmp->basePath) );
   for(size_t i =0 ; i<len ;i++){
       printf(" %c ",((char *)key)[i]);
   }
}

int main() {




    return 0;
}
