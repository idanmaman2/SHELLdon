//
// Created by idang on 9/18/22.
//

#ifndef IDSH_STACK_H
#define IDSH_STACK_H
#include <unistd.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>

typedef struct stack {
    size_t len ;
    unsigned int size  ;
    void * arr ;
};
struct stack *  create(unsigned int size ){
    struct stack *  stk = (struct stack * )malloc(sizeof (struct stack)*1);
    memset(stk,0,sizeof(stk));
    stk->size = size ;
    return stk ;


}
void * pop (struct stack * stk ){
    if(stk->len < 1){
        fprintf(stderr , "there are no elemnts in stack");
        exit(-1);
    }


}
void  push(void * ){}
void reset(){}
shot isEnd(){
    return stk->len ;
}
void free(){}
#endif //IDSH_STACK_H
