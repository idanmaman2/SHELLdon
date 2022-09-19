//
// Created by idang on 9/19/22.
//

#ifndef IDSH_TRIE_H
#define IDSH_TRIE_H

#include <malloc.h>
#include <memory.h>
#include "vector.h"

struct trieNode{
    void * end ;
    struct trieNode * next[26];
};



struct trie{
    struct trieNode root;
    int size ;
};




struct linkedNode * createTrieNode(void * data,int size){
    struct trieNode  * newHead = (struct trieNode * )malloc(sizeof(struct trieNode));
    memset(newHead,0,sizeof(struct trieNode));
    return newHead;

}
static int convertToIndex(char ch){
    return ch-'a';

}
static int nodeExsistChar(char ck , struct trieNode * nd){
    return nd->next[convertToIndex(ck)] ;
}

void putDataInTrieNode(struct trieNode * nd , int size , void * data){
    nd->end = malloc(size);
    memcpy(nd->end,data,size);
}


struct trie *  createTrie(size_t size ){
    struct trie *  stk = (struct trie * )malloc(sizeof (struct trie));
    memset(stk,0,sizeof(struct trie));
    stk->size = size ;
    return stk ;
}


void addWord (struct trie * nd , char * word , void * data ){
    int wordLen = strlen(word);
    struct trieNode * start = &nd->root;
    for(int i=0 ;i<wordLen;i++){
        if(!start->next[convertToIndex(word[i])])
            start->next[convertToIndex(word[i])] = malloc(sizeof(struct trieNode));
        start = start->next[convertToIndex(word[i])];
    }
    putDataInTrieNode(start,nd->size , data);
}

static void * searchForValueRec(struct trieNode * nd , char * word){
    if(*word)
        return searchForValueRec(nd->next[convertToIndex(*word)],word+1);
    return nd->end;
}
void *  searchForvalue(struct trie * nd , char * word ){
    return searchForValueRec(&nd->root,word);
}


static void forEachRec(void (*callback)(void * key , void * data , size_t keyLen),struct trieNode * node,struct vector * untilNow){
    char value ;
    addVector(&value,untilNow);
    if(node->end) {
        callback(untilNow->arr, node->end, untilNow->len-1);
    }
    for(size_t  i=0 ,value = 'a' ; i< 26 ; i++,value++){
        if(nodeExsistChar(value,node)){
            setIndexVector(untilNow->len-1,&value,untilNow);
            forEachRec(callback,node->next[convertToIndex(value)],untilNow);
        }

    }
    deleteLastVector(untilNow);



}

void forEachTrie(void (*callback)(void * ), struct trie * nd ){
    struct vector * vec = createVector(sizeof(char));
    forEachRec(callback,&nd->root,vec);


}




#endif //IDSH_TRIE_H
