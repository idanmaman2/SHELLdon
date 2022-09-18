//
// Created by idang on 9/17/22.
//

#ifndef IDSH_SHELLPRINTING_H
#define IDSH_SHELLPRINTING_H

#include <stdarg.h>
#include "vector.h"
#include <unistd.h>
#include <termios.h>
#define BLACK 30
#define GREEN 32
#define RED 31
#define YELLOW 33
#define  PURPLE 35
#define CYAN 36
#define WHITE 37
#define DEFAULTCOLOR 39

typedef struct command {
    int color ;
    char * command ;

} ;


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


char *  input (void (* callbackPrint) () )
{
    struct vector * vec = createVector(sizeof(char));
    char current;
    char end = 0 ;
    struct  vector * beforeSpace = createVector(sizeof(char));
    struct vector * commands = createVector(sizeof(struct command));
    struct  command com ;
    com.command = "ls\0";
    com.color = GREEN ;
    addVector( &com,commands );
    struct  command com2 ;
    com2.command = "echo\0";
    com2.color = RED ;
    addVector( &com2,commands );
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

        if(current == ' ' && beforeSpace->len > 0 ){
            int  color  = DEFAULTCOLOR ;
            addVector(&end,beforeSpace);
            for(size_t i =0 ; i<commands->len;i++){
                struct command * com =  (struct command *  )getIndexVector(i,commands);
                if(!strcmp(beforeSpace->arr,com->command) ){
                    color = com->color ;
                    break ;
                }

            }
            deleteLastVector(beforeSpace);
            forEach(clean,beforeSpace);
            printnf(beforeSpace->len,beforeSpace->arr , color);
            resetVector(beforeSpace);

        }
        else{
            if(beforeSpace > 0 )
                addVector(&current,beforeSpace);
        }
       printf("%c",current);
       fflush(stdout);
       addVector(&current,vec);


    } while(current != '\n');
    deleteVector(&end,vec);
    memset(vec->arr + (vec->len-1) * vec->size, 0 , vec->size);
    return  vec->arr;
}



#endif //IDSH_SHELLPRINTING_H
