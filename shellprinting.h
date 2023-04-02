//
// Created by idang on 9/17/22.
//

#ifndef IDSH_SHELLPRINTING_H
#define IDSH_SHELLPRINTING_H

#include <stdarg.h>
#include "DataStructers/vector.h"
#include "DataStructers/linkedList.h"
#include "DataStructers/trie.h"
#include "DataStructers/str.h"
#include "tokenizer.h"
#include <unistd.h>

#include <termios.h>
#define BLINK 5
#define BGWHITE 7
#define BGRED 41
#define BGGREEN 42
#define BGYELLOW 43
#define BGBLUE 44
#define BGPURPLE 45
#define BGCYAN 46
#define BGGRAY 101
#define BGGREEN2 102
#define BGYELLOW2 103
#define BGPRUPLE2 105
#define BGCYAN2 106
#define INVISABLE 8
#define BLACK 30
#define GREEN 32
#define RED 31
#define YELLOW 33
#define  PURPLE 35
#define CYAN 36
#define WHITE 37
#define system 1
#define intial 0
#define color_t int
#define command_t short
#define DEFAULTCOLOR 39
struct command {
    int color ;
    char * command ;

} ;
struct command_shell {
    struct str * basePath ;
    struct str * name ;
    command_t type ;
    color_t  colorShowHead ;
    color_t colorShowTail ;
    color_t def ;
} ;
static u_int8_t currentBGColor = 42;
u_int8_t getNextBG(){
    currentBGColor = (currentBGColor+1)%6 + 41 ;
    return  currentBGColor;
}

void changeColor(int color ) {
    printf("\033[0;%dm",color);
}

int getch() {
    struct termios oldtc;
    struct termios newtc;
    int ch;
    tcgetattr(STDIN_FILENO, &oldtc);
    newtc = oldtc;
    newtc.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newtc);
    ch=getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldtc);
    return ch;
}

void clean(void * arg){
    printf("\b");
    printf(" ");
    printf("\b");
    fflush(stdout);

}

void printnf(size_t n , char * string , int colorC){
    changeColor(colorC);
    for(size_t i =0 ; i< n ; i++)
        printf("%c", string[i]);
    changeColor(DEFAULTCOLOR);
    fflush(stdout);
}

char *  input (void (* callbackPrint) () , struct trie * tr )
{
    struct vector * vec = createVector(sizeof(char));
    char current;
    struct str * beforeSpace = createStr();
    do
    {
        current= getch();
        if (current == 127  ){
            if(vec->len > 0 ){
                deleteLastVector(vec);
                clean(NULL);
            }
            continue;
        }

        if(current == ' ' && beforeSpace->vec->len -1  > 0 ){
            int  color  = DEFAULTCOLOR ;
            struct command_shell * com = searchForvalue(tr,beforeSpace->vec->arr);
            if(com){
              color = com->colorShowTail;
            }
            forEachIter(clean,beforeSpace,NULL);
            printnf(beforeSpace->vec->len , beforeSpace->vec->arr,color);
            freeStr(beforeSpace);
            beforeSpace=createStr();

        }
        else{
            if(beforeSpace > 0 )
                addChrStr(current,beforeSpace);
        }


        printf("%c",current);
        fflush(stdout);
        addVector(&current,vec);


    } while(current != '\n');
    deleteVector(&end,vec);
    memset(vec->arr + (vec->len-1) * vec->size, 0 , vec->size);
    return  vec->arr;
}


struct str * inputv2(void (* callbackPrint) () , struct trie * tr ){

    struct str * commandString = createStr() ;
    char current =" ";
    do {

        current= getch();
        forEachIter(clean , commandString , NULL );
        if (current != 127  ){
            addChrStr(current , commandString);

        }
        else{
            deleteLastStr(commandString);
        }
        struct vector * tokens = tokenizer(commandString) ;
        for(int i=0 ,j=0  ; i < lengthStr(commandString) ; i++ ){
            struct TokenShell * currentToken = getIndexVector(j , tokens);
            if(currentToken && i > currentToken->end){
                currentToken = getIndexVector(++j , tokens) ;
            }
            if(currentToken && i <=  currentToken->end && i >= currentToken->start){
                switch (currentToken->type) {
                    case string:
                        changeColor(BGGREEN);
                        break;
                    case commandArgs :
                        changeColor(CYAN);
                        break ;
                    case pipeShell :
                        changeColor(YELLOW);
                        break ;
                    case backgroundShell :
                        changeColor(PURPLE);
                        break ;
                    case command :
                        changeColor(BGBLUE);
                        struct str * commandSubStr = subStr(currentToken->start , currentToken->end , commandString);
                        struct command_shell * com = searchForvalue(tr,commandSubStr->vec->arr);
                        if(!com){
                            changeColor(RED);
                        }
                        break ;

                }
            }
            else{
                changeColor(DEFAULTCOLOR);
            }
            putchar(getIndexStr(i , commandString));


        }


    } while(current != '\n');
    return commandString ;





}




#endif //IDSH_SHELLPRINTING_H