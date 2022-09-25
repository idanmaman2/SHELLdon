//
// Created by idang on 9/19/22.
//

#ifndef IDSH_SHELLCORE_H
#define IDSH_SHELLCORE_H
#define command_t short
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include "DataStructers/vector.h"
#include "DataStructers/trie.h"
#include "DataStructers/str.h"

#define system 1
#define intial 0
#define color_t int
struct command_shell {
    struct str * basePath ;
    struct str * name ;
    command_t type ;
    color_t  colorShowHead ;
    color_t colorShowTail ;
    color_t def ;
} ;

int isRunAble(char * path ){
    struct stat st ;
    lstat(path,&st);
    stat(path, &st) == 0 &&
    st.st_mode & S_IXUSR && S_ISREG(st.st_mode);

}

char * getFullPath(char * path,char * command ){
    struct vector * vec = createVector(sizeof(char));
    for(size_t i=0 ; i < strlen(path) ;i ++ )
        addVector(path+i,vec);
    if(*((char *) getLastVector(vec)) != '/'){
        char value = '/';
        addVector(&value , vec);
    }
    char value=0;
    addVector(&value,vec);
    struct dirent *d;
    DIR *dh = opendir(vec->arr);
    char * fullPath ;
    while ((d = readdir(dh)) != NULL)
    {
        fullPath = (char * ) malloc(sizeof(char)*(vec->len+ strlen(d->d_name)));
        strcpy(fullPath,vec->arr);
        strcat(fullPath,d->d_name);
        //If hidden files are found we continue

        if (d->d_name[0] != '.' && isRunAble(fullPath)){
            if(!strcmp(command,d->d_name))
                return fullPath;
        }
    }
    return  NULL;



}

void allCommandsP(struct str  * path ,struct vector * out ){
    if(getLastStr(path) != '/')
        addChrStr('/' , path);
    struct dirent *d;
    DIR *dh = opendir(path->vec->arr);
    if(!dh)
        return ;
    while ((d = readdir(dh)) != NULL)
    {
        struct str * fullPath = clone(path);
        addChrArrStr(d->d_name,fullPath);
        if (d->d_name[0] != '.' && isRunAble(fullPath->vec->arr)){
            struct command_shell * com = malloc(sizeof(struct command_shell));
            com->basePath = clone(path);
            com->name= createStrChar(d->d_name);
            com->colorShowHead = BGBLUE ;
            com->colorShowTail =BGPURPLE ;
            com->def = BGYELLOW ;
            com->type = system;
            addVector(com,out);
        }
    }
}

struct vector * getPath(){
    struct str * st  = createStrChar(getenv("PATH"));
    void * sp = split(st,':');
    freeStr(st);
    return sp ;
}

void printPath(void * data , int * arg ){
    (*arg)++;
    struct command_shell * dataV = data;
    changeColor(dataV->def);
    printf("%d . path : ",*arg) ;
    changeColor(dataV->colorShowHead);
    printf(dataV->name->vec->arr );
    changeColor(dataV->def);
    printf(" name :  ") ;
    changeColor(dataV->colorShowTail);
    printf(dataV->basePath->vec->arr);
    changeColor(DEFAULTCOLOR);
    printf("\n");
}

struct vector *  allCommands(  ){

    struct vecotr * out = createVector(sizeof(struct command_shell));
    struct vector * path = getPath();
    for(size_t i=0;i<path->len;i++){
        allCommandsP(getIndexVector(i,path),out);
    }
    return out ;

}
void printAllCommamnds(void (* callBack )(void * data , void  * args )){
    int arg =0 ;
    forEachIter(callBack,allCommands(),&arg );
}
struct command_shell * searchForCommand(char * name ){
    struct vector * PATH = getPath();
    for(size_t i=0;i<PATH->len;i++){
        struct str * path = getIndexVector(i,PATH);
        if(getLastStr(path) != '/')
            addChrStr('/' , path);
        struct dirent *d;
        DIR *dh = opendir(path->vec->arr);
        if(!dh)
            continue;
        while ((d = readdir(dh)) != NULL)
        {
            struct str * fullPath = clone(path);
            addChrArrStr(d->d_name,fullPath);
            if (d->d_name[0] != '.' && isRunAble(fullPath->vec->arr)&& !strcmp(d->d_name,name)){
                struct command_shell * com = malloc(sizeof(struct command_shell));
                com->basePath = clone(path);
                com->name= createStrChar(d->d_name);
                com->colorShowHead = BGBLUE ;
                com->colorShowTail =BGPURPLE ;
                com->def = BGYELLOW ;
                com->type = system;
                return com ;
            }
        }
    }
    return NULL;
}


void justDoIt(char * path  , char ** args ){
    int status ;
    if( fork()){
        wait(&status);
    }
    else{
        changeColor(CYAN);
        execv(path,args);
        fflush(stdout);
        changeColor(DEFAULTCOLOR);
    }
}


#endif //IDSH_SHELLCORE_H