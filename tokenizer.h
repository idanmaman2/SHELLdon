//
// Created by Idan Maman on 02/04/2023.
//

#ifndef IDSH_TOKENIZER_H
#define IDSH_TOKENIZER_H


#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "DataStructers/str.h"

struct token{
    size_t start;
    size_t end ;
    char type ;
};
enum TokenType{command , commandArgs  , string , pipeShell ,backgroundShell ,operator } ;

struct TokenShell {
    short  type;
    size_t start ;
    size_t end ;
};

enum seriesType{None =0 , space = 1  , Str1 = 2   , Str2 = 3   };


struct TokenShell * createToken(size_t start , size_t end  , short type){
    struct TokenShell * res = malloc(sizeof(struct TokenShell)) ;
    res->start = start ;
    res->end = end ;
    res->type = type ;
    return res ;
}

void freeToken(struct TokenShell * tok ){
    free(tok) ;
}

struct vector *  tokenizer(struct str * command_raw){
    struct vector *  tokens = createVector(sizeof(struct TokenShell)) ;

    for(size_t i = 0 , start = 0 , series = None ; i< lengthStr(command_raw);i++){
        char chCurrent = getIndexStr(i , command_raw) ;
        switch (chCurrent) {
            case ' ':
                if (series != None || start == i ) {
                    if(start == i){
                        series = space ;
                        start= i+1 ;
                    }
                    continue;
                }
                // if it is None - means we are not in string ...
                char typeofToken = command ;
                struct TokenShell * lastToken = getLastVector(tokens);
                if( lastToken  && (lastToken->type == command || lastToken->type == commandArgs || lastToken->type == string) ) {
                    typeofToken = commandArgs ;
                }
                struct Token *tok = createToken(start, i - 1, typeofToken);
                addVector(tok, tokens);
                freeToken(tok);
                start = i + 1;
                series = space ;
                break;
            case '|':
                if (series != None && series != space)
                    continue;
                // if it is None - means we are not in string ...
                if (series == NULL) {
                    struct TokenShell *tok1 = createToken(start, i - 1, pipeShell);
                    addVector(tok1, tokens);
                    freeToken(tok1);
                }
                {
                    struct TokenShell *tok2 = createToken(i, i, pipeShell);
                    addVector(tok2, tokens);
                    freeToken(tok2);
                }
                start = i + 1;
                series = None ;

                break;
            case '&' :
                if (series != None && series != space)
                    continue;
                // if it is None - means we are not in string ...
                if (series == NULL) {
                    struct TokenShell *tok1 = createToken(start, i - 1, backgroundShell);
                    addVector(tok1, tokens);
                    freeToken(tok1);
                }
                {
                    struct TokenShell *tok2 = createToken(i, i, backgroundShell);
                    addVector(tok2, tokens);
                    freeToken(tok2);
                }
                start = i + 1;
                series = None ;

                break;
            case '"':
                if (series == Str2)
                    continue;
                if (series == Str1) {
                    struct TokenShell *tok = createToken(start, i, string);
                    addVector(tok, tokens);
                    freeToken(tok);
                    series = None ;
                    start = i +1 ;
                } else {//series == None or space
                    start = i;
                    series = Str1;
                }
                break;
            case '\'':
                if (series == Str1)
                    continue;
                if (series == Str2) {
                    struct TokenShell *tok = createToken(start, i, string);
                    addVector(tok, tokens);
                    freeToken(tok);
                    series = None ;
                    start = i +1 ;
                } else { //series == None or space
                    start = i;
                    series = Str2;
                }
                break;
            default:
                if (series == space ){
                    series = None ;
                }
                if( i == lengthStr(command_raw) -1 && start != i ){
                    struct Token *tok = createToken(start, i - 1, command);
                    addVector(tok, tokens);
                    freeToken(tok);
                }


        }



    }




    return tokens ;
}

#endif //IDSH_TOKENIZER_H
