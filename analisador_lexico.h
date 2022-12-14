#include <stdio.h>
#include "tabeladesimbolos.h"

#define nSymbols 26
enum {LETRA=nSymbols, DIGITO, INVALIDO};

enum tKeyword {ELSE, FUNCTIONS, GOTO, IF, LABELS, RETURN, VAR, VARS, VOID, WHILE, nKeywords};
enum tTerminal {ID=nKeywords, CONST, ADDOP, OR, MULOP, NOT, SEMICOLON, ASSIGN, COLON, COMMA, LCB, RCB, LB, RB, LP, RP, RELOP, FIM_ARQ, nTerminal};
enum tErros{ERRO_LEXICO=nTerminal, ERRO_SINTATICO};
extern int lines;
extern char lexema[100];
extern char *terminais[];
extern FILE *fin;

char checaKeyword (char *s);
int lex();
