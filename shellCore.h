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
   void * basePath ;
    command_t type ;
    color_t  colorShow ;
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

void allCommandsP(char * path ,struct vector * out ){
    struct vector * vec = createVector(sizeof(char));
    addNVector(path, strlen(path),vec);
    if(*((char *) getLastVector(vec)) != '/'){
        char value = '/';
        addVector(&value , vec);
    }
    char value=0;
    addVector(&value,vec);
    struct dirent *d;
    DIR *dh = opendir(vec->arr);
    if(!dh)
        return ;
    char * fullPath ;
    while ((d = readdir(dh)) != NULL)
    {
        printf("cool");
        if (d->d_name[0] != '.' && isRunAble(fullPath)){
            printf("cool %s \n ",d->d_name);
            fflush(stdout);
            struct vector * vec2 = createVector(sizeof(char));
            addNVector(d->d_name,strlen(d->d_name)+1,vec2);
            addVector(&end,vec2);
            addVector(vec2,out);
        }
    }
    printf("cool path env is %s ",path);
    fflush(stdout);
}

struct vector * getPath(){

    struct vector * res = createVector(sizeof(struct vector));
    char *  PATH= getenv("PATH");

    struct vector * vecPATH = createVector(sizeof(char));
    addNVector(PATH, strlen(PATH),vecPATH);

    char * token = strtok(vecPATH->arr,":\0");
    while(token){
        struct vector * cr = createVector(sizeof(char));
        addNVector(token , strlen(token),cr);
        addVector(&end,cr);
        addVector(cr,res);
        token=strtok(NULL,":\0");
    }
    return res ;
}

void printPath(void * data){
    struct vector * dataV = data;
    printf("path : %s\n",((char * ) dataV->arr));
}

void allCommands( ){

    struct vecotr * out = createVector(sizeof(struct vector));
    struct vector * path = getPath();
    for(size_t i=0;i<path->len;i++){
        struct vector * dataV = getIndexVector(i,path);
        allCommandsP(dataV->arr,out);
    }

    forEachIter(printPath,out,NULL);





}

#endif //IDSH_SHELLCORE_H
