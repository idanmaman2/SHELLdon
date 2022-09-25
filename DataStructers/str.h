//
// Created by idang on 9/20/22.
//

#ifndef IDSH_STR_H
#define IDSH_STR_H

#include "vector.h"

char end = 0 ;
struct str {
    struct iter  it ;
    struct vector * vec ;
} ;

//iter

void * iterNextStr( int  * current,struct str * ln){

    return getIndexVector((*current)++ , ln->vec);
}

int iterHasNextStr(int  * current,struct str * ln){
    return *current  < ln->vec->len-1;
}

void iterResetStr(int * current,struct str * ln){
    *current = 0 ;
}


//functions

struct str *  createStr(){
    struct str * tmp = malloc(sizeof(struct str));
    tmp->vec= createVector(sizeof(char));
    addVector(&end,tmp->vec);
    tmp->it.current = malloc(sizeof(int));
    *((int *)  tmp->it.current)=0 ;
    tmp->it.next=iterNextStr;
    tmp->it.reset=iterResetStr;
    tmp->it.hasNext=iterHasNextStr;
    return tmp ;
}

struct str * clone(struct str *  st){
    struct str * jon = malloc(sizeof(struct str ));
    jon->vec = cloneVector(st->vec);
    return jon;
}

void addChrStr(char con , struct str *  st ){
    addVector(&end , st->vec);
    setIndexVector(st->vec->len-2 ,&con , st->vec );

}

void addChrArrStr(char *  con , struct str *  st ){
    for(size_t i=0 ;i<strlen(con)+1;i++ ){
        if(!i)
            setIndexVector(st->vec->len-1 , con+i,st->vec);
        else
            addVector(con+i,st->vec);
    }


}

void deleteLastStr(struct str *  st ){

    deleteLastVector(st->vec);
    setIndexVector(st->vec->len-1 ,&end , st->vec );


}

size_t  findStrIndex(struct str *  st,char * search ){
    return (strstr(st->vec->arr ,search ) - (char *)st->vec->arr);
}

struct vector *  split(struct str *  st , char d ){
    struct str * deli = createStr();
    char d2[2] =" ";
    d2[0]=d;
    struct vector * res = createVector(sizeof(struct str));
    struct str * cloned = clone(st);
    char * token = strtok(cloned->vec->arr,d2);
    while(token){
        struct str * cr = createStr();
        addChrArrStr(token,cr);
        addVector(cr,res);
        token=strtok(NULL,d2);
    }
    return res ;
}

void catStr(struct str *  dest,struct str *  src){
    setIndexVector(dest->vec->len-1 , src->vec->arr , dest->vec);
    addNVector(src->vec->arr+sizeof(char),src->vec->len-1,dest->vec);
}

struct str * join(struct vector * arr , char d ){
    struct str * jon = createStr();
    struct str * arrS = arr->arr ;
    for(size_t i =0 ;i<arr->len;i++){
        catStr(jon,arrS+i);
        if(i !=  arr->len -1 )
            addChrStr(d , jon);
    }
    return jon;


}

#endif //IDSH_STR_H
