//
// Created by idang on 9/21/22.
//

#ifndef IDSH_ITER_H
#define IDSH_ITER_H
struct iter {
    void *  (*next) ();
    void (*reset)();
    int  (*hasNext )();
    void * current ;
};

void forEachIter(void (*func ) , struct iter * it  , void  * ds ){}
void convertToVectorIter(struct iter * it , void * ds ){}
void mapIter(void (*func ) , struct iter * it , void * ds ){}
void filterIter(int (*func ) , struct iter * it , void * ds  ){}
void reduceIter(int (*func ) , struct iter * it , void * ds ){}




#endif //IDSH_ITER_H
