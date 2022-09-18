//
// Created by idang on 9/19/22.
//

#ifndef IDSH_TRIE_H
#define IDSH_TRIE_H

#include <malloc.h>
#include <memory.h>

struct trieNode{
    void * end ;
    struct trieNode * next[26];
};



struct trie{
    struct trieNode * next[26];
    int size ;
};

struct linkedNode * createTrieNode(void * data,int size){
    struct trieNode  * newHead = (struct trieNode * )malloc(sizeof(struct trieNode));
    memset(newHead,0,sizeof(struct trieNode));
    return newHead;

}

void pustDataInTrieNode(struct trieNode * nd , int size , void * data){
    nd->end = malloc(size);
    memcpy(nd->end,data,size);
}


struct linkedList *  createTrie(unsigned int size ){
    struct trie *  stk = (struct trie * )malloc(sizeof (struct trie);
    memset(stk,0,sizeof(struct trie));
    stk->size = size ;
    return stk ;
}


#endif //IDSH_TRIE_H
