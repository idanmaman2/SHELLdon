//
// Created by idang on 9/18/22.
//

#ifndef IDSH_STACK_H
#define IDSH_STACK_H
#include <unistd.h>
typedef struct stack {
    size_t len ;
    unsigned int size  ;
    void * arr ;
};
void create(unsigned int size ){}
void * pop (){}
void  push(void * ){}
void reset(){}
void free(){}
#endif //IDSH_STACK_H
