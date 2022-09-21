%{
    #include <stdio.h>
    #include <string.h>
    char output[50];
    int yyline;
    #define write fwrite(output, strlen(output), 1, yyout);
%}

%%

\n  yyline++;/*contador de linhas*/
[ \t\n]+    /*não faz nada quando encontra espaço*/

        /*operadores de adição*/
"+"     sprintf(output, "line: %d token: ADDOP value: +\n", yyline); write;
"-"     sprintf(output, "line: %d token: ADDOP value: -\n", yyline); write;
"||"    sprintf(output, "line: %d token: ADDOP value: OR\n", yyline); write;

        /*operadores de multiplicação*/
"*"     sprintf(output, "line: %d token: MULOP value: *\n", yyline); write;
"/"     sprintf(output, "line: %d token: MULOP value: /\n", yyline); write;
"&&"    sprintf(output, "line: %d token: MULOP value: AND\n", yyline); write;

        /*Subistituir por um título genérico*/
"!"    sprintf(output, "line: %d token: NOT\n", yyline); write;
";"    sprintf(output, "line: %d token: SEMICOLON\n", yyline); write;
"="    sprintf(output, "line: %d token: ASSIGN\n", yyline); write;
":"    sprintf(output, "line: %d token: COLON\n", yyline); write;
","    sprintf(output, "line: %d token: COMMA\n", yyline); write;
"{"    sprintf(output, "line: %d token: LCB\n", yyline); write;
"}"    sprintf(output, "line: %d token: RCB\n", yyline); write;
"["    sprintf(output, "line: %d token: LB\n", yyline); write;
"]"    sprintf(output, "line: %d token: RB\n", yyline); write;
"("    sprintf(output, "line: %d token: LP\n", yyline); write;
")"    sprintf(output, "line: %d token: RP\n", yyline); write;

        /*Adicionar constantes e ID*/
[0-9][0-9]*     sprintf(output, "line: %d token: CONST value: %s\n", yyline, yytext); write;
[a-zA-Z][a-zA-Z0-9]*    sprintf(output, "line: %d token: ID value: %s\n", yyline, yytext); write;

        /*Adicionar operadores relacionais*/ 
"=="    sprintf(output, "line: %d token: RELOP value: EQ\n", yyline); write;
"!="    sprintf(output, "line: %d token: RELOP value: NEQ\n", yyline); write;
"<"     sprintf(output, "line: %d token: RELOP value: LT\n", yyline); write;
">"     sprintf(output, "line: %d token: RELOP value: GT\n", yyline); write;
"<="    sprintf(output, "line: %d token: RELOP value: LEQ\n", yyline); write;
">="    sprintf(output, "line: %d token: RELOP value: GEQ\n", yyline); write;
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
