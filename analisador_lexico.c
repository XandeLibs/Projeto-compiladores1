#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "analisador_lexico.h"

char lexema[100];
int lines = 1, lextam;
char c;

char *keywords[] = {
    "boolean", "else", "false", "functions", "goto", "if", "integer", "labels", "read", "return", "true", "var", "vars", "void", "while", "write"
};

char *terminais[] = {
    "integer", "boolean", "true", "false", "read", "write", "void", "while", "if", "return", "goto", "functions", "labels", "vars", "var", "else", "ID", "CONST",
    "ADDOP", "OR", "MULOP", "NOT", "SEMICOLON", "ASSIGN", "COLON", "COMMA", "LCB", "RCB", "LB", "RB", "LP", "RP", "RELOP"
};

char checaKeyword(char *c){

    int lim_esq, lim_dir, meio, x;

    lim_esq=0;                                  //começo da lista de keyword
    lim_dir=nKeywords-1;                        //final da lista de keyword
    while(lim_esq <= lim_dir){                  //passa por toda a lista
        meio = (lim_esq + lim_dir)/2;           //busca binaria
        if((x=strcmp(c,keywords[meio]))>0){     //compara o lexema recebido como parametro com uma palavra reservada
            lim_esq = meio+1;
        }
        else if(x<0){
            lim_dir = meio-1;
        }
        else{
            return meio;
        }
    }
    return ID;
    
}

int lex()
{
    int estado_atual, prox_estado, next, t;

    lextam = 0;
    estado_atual = 0;

    do{
    c = getc(fin);
    lexema[lextam++] = c;
    lexema[lextam] = '\0';

    switch(estado_atual){
    case 0:
    switch(c){
    case '\n':
        lines++;
    case '\t':
    case ' ':
        lextam--;
        break;
    case '+':
        return ADDOP;
    case '-':
        return ADDOP;
    case '|':
        estado_atual = 1;
    case '*':
        return MULOP;
    case '/':
        return MULOP;
    case '&':
        estado_atual = 2;
        break;
    case '!':
        estado_atual = 3;
        break;
    case ';':
        return SEMICOLON;
    case '=':
        estado_atual = 4;
        break;
    case ':':
        return COLON;
    case ',':
        return COMMA;
    case '{':
        return LCB;
    case '}':
        return RCB;
    case '[':
        return LB;
    case ']':
        return RB;
    case '(':
        return LP;
    case ')':
        return RP;
    case '<':
        estado_atual = 5;
        break;
    case '>':
        estado_atual = 5;
        break;
    default:
        if(isdigit(c)){
            estado_atual = 6;
        }
        else if(isalpha(c)){
            estado_atual = 7;
        }
        else if(!feof(fin))
            return ERRO_LEXICO;
            break;
        }
        break;
    case 1:
        if(c == '|'){
            return OR;
        }
        else{
            return ERRO_LEXICO;
        }
    case 2:         //achou '&', espera outro
        if(c == '&'){
            return MULOP;
        }
        else{
            return ERRO_LEXICO;
        }
    case 3:         //achou '!', espera '=' ou algo diferente
        if(c=='='){
            return RELOP;
        }
        else{
            ungetc(c,fin);
            lexema[--lextam]='\0';
            return NOT;
        }
    case 4:         //achou '=', espera outro ou algo diferente
        if(c=='='){
            return RELOP;
        }
        else{
            ungetc(c,fin);
            lexema[--lextam]='\0';
            return ASSIGN;
        }
    case 5:         //achou '<' ou '>', espera '=' ou algo diferente
        if(c!='='){
            ungetc(c,fin);
            lexema[--lextam]='\0';
        }
        return RELOP;
    case 6:         //achou digito
        if(!isdigit(c)){
            ungetc(c,fin);
            lexema[--lextam]='\0';
            return CONST;
        }
        break;
    case 7:         //achou char
        if(!isalpha(c) && !isdigit(c)){
            ungetc(c,fin);
            lexema[--lextam]='\0';
            return (checaKeyword(lexema));
        }
        break;     
    }    
    } while(!feof(fin));
        if(estado_atual==0){ /* fim de arquivo */
            lexema[0]='\0';
            return FIM_ARQ;
    }
    return ERRO_LEXICO;
}
