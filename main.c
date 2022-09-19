#include <stdio.h>
#include <stdlib.h>
#include "shellprinting.h"
#include "DataStructers/linkedList.h"
#include "DataStructers/trie.h"

#define true 1
#define INT_MAX 2147483647

void print2(void * param,void * data , size_t len)
{
   printf("data %d ", *((int * )data));
    fflush(stdout);
   for(size_t i=0; i< len ;i++){
       printf("%c ",((char *)param)[i]);
       fflush(stdout);
   }
}


int main() {

    int data = 3 ;
    struct trie * tr = createTrie(sizeof(int));
    printf("hi");
    fflush(stdout);
    addWord(tr,"idan",&data);
    data=8;
    printf("hi");
    fflush(stdout);
    addWord(tr,"iadn",&data);
    printf("hi");
    fflush(stdout);
    forEachTrie(print2,tr);
    printf("hi");

    return 0;

}
