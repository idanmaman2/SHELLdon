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

void printStr( struct str * st2 , void * ){
    printf("cool : %s \n",st2->vec->arr);
    fflush(stdout);
}

void printChar( char * ch ){
    printf("cool : %c \n",*ch);
    fflush(stdout);
}

void printAll(void * key , void  * data, size_t len ){
   struct command_shell * tmp = data;
   printf("\ntype : %d color : %d , basePath: %s \n" ,tmp->type ,tmp->colorShowHead , ((char * ) tmp->basePath) );
   for(size_t i =0 ; i<len ;i++){
       printf(" %c ",((char *)key)[i]);
   }
}

void addToTrie(struct command_shell * c , struct trie * t ){
    addWord(t,c->name->vec->arr,c);
}

void prt(char * key , void * x, int size){
    for(int i=0;i<size;i++){
        printf("%c",key[i]);
    }
}


int main() {




  homedir = getenv("HOME");
  username= getenv("USER");
  int i =0 ;
  printAllCommamnds(printPath);

    int x = 3;
    struct trie * tr = createTrie(sizeof(struct command_shell));
    forEachIter(addToTrie,allCommands(),tr);
    forEachTrie(prt,tr);





    while(true ){
      printSchemeToscreen();
      struct str  * input2 = createStrChar(input(printSchemeToscreen,tr));
      struct vector * sp = split(input2,' ');
      char * * arr = malloc(sp->len * sizeof(char * )+1);
      arr[sp->len] = NULL ;
      struct str * com = sp->arr ;
      struct command_shell * cm = searchForCommand(com->vec->arr);
      struct str * full = clone(cm->basePath);
      catStr(full, cm->name);
      arr[0] = full->vec->arr ;
      for(size_t i = 1 ; i<sp->len ; i++ ){
          struct str * arg = sp->arr + sp->size * i ;
          arr[i] = arg->vec->arr;
      }
      justDoIt(full->vec->arr , arr);
  }


    return 0;
}
