#include <stdio.h>

#define nSymbols 26
enum {LETRA=nSymbols, DIGITO, INVALIDO};

enum tKeyword {INTEGER, BOOLEAN, TRUE, FALSE, READ, WRITE, VOID, WHILE, IF, RETURN, GOTO, FUNCTIONS, LABELS, VARS, VAR, ELSE, nKeywords};
enum tTerminal {ID=nKeywords, CONST, ADDOP, OR, MULOP, NOT, SEMICOLON, ASSIGN, COLON, COMMA, LCB, RCB, LB, RB, LP, RP, RELOP, FIM_ARQ, nTerminal};
enum tErros{ERRO_LEXICO=nTerminal, ERRO_SINTATICO};
extern int lines;
extern char lexema[100];
extern char *terminalName[];
extern FILE *fin;

char nextSymbol (FILE* fin);
char checaKeyword (char *s);
int lex();
