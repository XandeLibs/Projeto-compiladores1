%{
    #include <stdio.h>
    #include <string.h>
    char output[50];
    int yyline;
%}

/*Definições macros*/
digit [0-9]
integer {digit}+
letter [a-zA-Z]
identifier [a-zA-Z][a-zA-Z0-9]*
empty [ ]

%%

\n  yyline++;/*contador de linhas*/
[ \t\n]+ ;   /*não faz nada quando encontra espaço*/
{empty}+ ;

        /*operadores de adição*/
"+"     sprintf(output, "line: %d token: ADDOP value: +\n", yyline); fwrite(output, strlen(output), 1, yyout);;
"-"     sprintf(output, "line: %d token: ADDOP value: -\n", yyline); fwrite(output, strlen(output), 1, yyout);;
"||"    sprintf(output, "line: %d token: ADDOP value: OR\n", yyline); fwrite(output, strlen(output), 1, yyout);;

        /*operadores de multiplicação*/
"*"     sprintf(output, "line: %d token: MULOP value: *\n", yyline); fwrite(output, strlen(output), 1, yyout);;
"/"     sprintf(output, "line: %d token: MULOP value: /\n", yyline); fwrite(output, strlen(output), 1, yyout);;
"&&"    sprintf(output, "line: %d token: MULOP value: AND\n", yyline); fwrite(output, strlen(output), 1, yyout);;

        /*Substituir por um título genérico*/
"!"    sprintf(output, "line: %d token: NOT\n", yyline); fwrite(output, strlen(output), 1, yyout);;
";"    sprintf(output, "line: %d token: SEMICOLON\n", yyline); fwrite(output, strlen(output), 1, yyout);;
"="    sprintf(output, "line: %d token: ASSIGN\n", yyline); fwrite(output, strlen(output), 1, yyout);;
":"    sprintf(output, "line: %d token: COLON\n", yyline); fwrite(output, strlen(output), 1, yyout);;
","    sprintf(output, "line: %d token: COMMA\n", yyline); fwrite(output, strlen(output), 1, yyout);;
"{"    sprintf(output, "line: %d token: LCB\n", yyline); fwrite(output, strlen(output), 1, yyout);;
"}"    sprintf(output, "line: %d token: RCB\n", yyline); fwrite(output, strlen(output), 1, yyout);;
"["    sprintf(output, "line: %d token: LB\n", yyline); fwrite(output, strlen(output), 1, yyout);;
"]"    sprintf(output, "line: %d token: RB\n", yyline); fwrite(output, strlen(output), 1, yyout);;
"("    sprintf(output, "line: %d token: LP\n", yyline); fwrite(output, strlen(output), 1, yyout);;
")"    sprintf(output, "line: %d token: RP\n", yyline); fwrite(output, strlen(output), 1, yyout);;

        /*Adicionar constantes e ID*/
{integer}               sprintf(output, "line: %d token: CONST value: %s\n", yyline, yytext); fwrite(output, strlen(output), 1, yyout);;
{identifier}+           sprintf(output, "line: %d token: ID value: %s\n", yyline, yytext); fwrite(output, strlen(output), 1, yyout);;

        /*Adicionar operadores relacionais*/ 
"=="    sprintf(output, "line: %d token: RELOP value: EQ\n", yyline); fwrite(output, strlen(output), 1, yyout);;
"!="    sprintf(output, "line: %d token: RELOP value: NEQ\n", yyline); fwrite(output, strlen(output), 1, yyout);;
"<"     sprintf(output, "line: %d token: RELOP value: LT\n", yyline); fwrite(output, strlen(output), 1, yyout);;
">"     sprintf(output, "line: %d token: RELOP value: GT\n", yyline); fwrite(output, strlen(output), 1, yyout);;
"<="    sprintf(output, "line: %d token: RELOP value: LEQ\n", yyline); fwrite(output, strlen(output), 1, yyout);;
">="    sprintf(output, "line: %d token: RELOP value: GEQ\n", yyline); fwrite(output, strlen(output), 1, yyout);;

        /*Identificando as palavras reservadas*/ 
integer|boolean|true|false|read|write|void|while|if|return|goto|type|function|label|var|else {sprintf(output, "line: %d token: KEY value: %s\n", yyline, yytext); fwrite(output, strlen(output), 1, yyout);;} 

%%

int yywrap(void){
    return 1;
}

int main(void){
    yyin = fopen("in.txt", "r");
    yyout = fopen("out.txt", "w");
    yylex();
    fclose(yyin);
    return 0;
}
