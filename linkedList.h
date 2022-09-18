//
// Created by idang on 9/18/22.
//

#ifndef IDSH_STACK_H
#define IDSH_STACK_H
#include <unistd.h>
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>

typedef  struct linkedNode {
    struct  linkedNode * next ;
    struct  linkedNode * before ;
    void * content ;
};

typedef struct linkedList {
    size_t len ;
    unsigned int size  ;
    struct linkedNode * head  ;
    struct linkedNode * tail ;
};

void freeNode(struct linkedNode * node){
    free(node->content);
    free(node);
}

struct linkedNode * createNode(void * data,int size){
    struct linkedNode  * newHead = (struct linkedNode * )malloc(sizeof(struct linkedNode));
    memset(newHead,0,sizeof(struct linkedNode));
    newHead->content=malloc(size);
    memcpy(newHead->content,data,size);
    return newHead;

}

struct linkedList *  createLinkedList(unsigned int size ){
    struct linkedList *  stk = (struct linkedList * )malloc(sizeof (struct linkedList));
    memset(stk,0,sizeof(struct linkedList));
    stk->size = size ;
    return stk ;
}

void pushFront(struct linkedList * ln ,void * data){
    struct linkedNode  * newHead = createNode(data,ln->size);
    newHead->next=ln->head;
    if(ln->head)
        ln->head->before=newHead;
    else
        ln->tail=newHead;
    ln->head=newHead;
}

void pushBack(struct linkedList * ln , void * data ){
    struct linkedNode  * newHead = createNode(data,ln->size);
    if(!ln->tail){
        ln->head=newHead;
        ln->tail=newHead;
        return ;
    }
    newHead->before = ln->tail ;
    ln->tail->next=newHead;
    ln->tail=newHead;
}

void *  getFront (struct linkedList * ln ){
    return ln->head->content;
}

void *  getBack(struct linkedList * ln ){
    return ln->tail->content;
}

void * popFront(struct linkedList * ln){
    struct linkedNode * toDel = ln->head;
    ln->head=ln->head->next;
    freeNode(toDel);

}

void * popBack(struct linkedList * ln){
    struct linkedNode * toDel = ln->tail;
    ln->tail=ln->tail->before;
    ln->tail->next=NULL;
    freeNode(toDel);

}
void forEachLinked(void (*function)(void * param),struct linkedList * ln){
    struct linkedNode * start = ln->head;
    while(start){
        function(start->content);
        start=start->next;
    }

}


#endif //IDSH_STACK_H
