//
// Created by idang on 9/14/22.
//
#include<malloc.h>
#include <memory.h>
#include <assert.h>
#include <stdlib.h>

#ifndef UNTITLED1_VECTOR_H
#define UNTITLED1_VECTOR_H

typedef  struct vector
{
    void  * arr;
    int size ;
    int len;
};

struct vector * createVector(int size ){
    struct vector * vec = (struct vector * )malloc(sizeof(struct vector));
    memset(vec , 0 , sizeof(struct vector));
    if(size <=0 ){
        fprintf(stderr , "cant create vector of size 0");
        exit(-1);
    }
    vec->size=size;
    return  vec ;
}

void addVector(void * content , struct  vector *  vec ){
    vec->arr = realloc( vec->arr, vec->size * ++vec->len);
    memcpy( vec->arr + (vec->size ) * (vec -> len -1 ) ,content , vec-> size  );
}

int searchVector(void *  content , struct vector* vec){
    for(size_t index =0 ; index<vec->len;index++){
        if(!memcmp(content,vec->arr+index*vec->size,vec->size))
            return index;
    }
    return -1;

}

int deleteIndexVector(size_t index  ,struct vector * vec ){
    if(index < 0 || index >= vec->len|| vec -> len < 1 )
        return  -1 ;
    void * arrNew = malloc(vec->size * --vec->len);
    memcpy(arrNew , vec->arr , (index)* vec->size   );
    memcpy(arrNew +(index+1)*vec->size    ,arrNew + (index) * vec->size , (vec->len-index)*vec-> size  );
    free(vec->arr);
    vec->arr=arrNew ;
    return index;

}

int deleteVector(void * content  ,struct vector * vec ){
    return deleteIndexVector(searchVector(content,vec),vec);
}

void * deleteLastVector(struct vector * vec){
    deleteIndexVector(vec->len - 1 , vec ) ;

}

void * setIndexVector(size_t index , void * data , struct vector * vec){
    memcpy(vec->arr + index * vec->size , data,vec->size);
}

void * getIndexVector(size_t index , struct vector * vec){
    return vec->arr + vec->size * index  ;
}

void * getLastVector(struct vector * vec ){
    return getIndexVector(vec->len-1 , vec);
}

void freeVector(struct vector * vec){
    if(vec->len > 0 ){
        free(vec->arr);
    }
    vec->arr = NULL;

}

void resetVector(struct vector * vec){
    freeVector(vec);
    vec->len=0;
}

void forEach(void (*callback)(void * x), struct vector * vec){
    for(int i = 0 ; i<vec->len ;i++)
        callback(vec->arr + i * vec->size );
}

void fornEach(void (*callback)(void * x), size_t len , struct vector * vec){
    if(len > vec->len){
        fprintf(stderr ,"cant loop , segmation error");
        exit(-1);
    }

    for(int i = 0 ; i<len ;i++)
        callback(vec->arr + i * vec->size );
}

void sortVector(struct vector * vec , int (* compare )(const void * a , const void * b )){
    qsort(vec->arr,vec->len , vec->size  , compare );
}

#endif //UNTITLED1_VECTOR_H
