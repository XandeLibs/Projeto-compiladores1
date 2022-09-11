%{
    #include <stdio.h>
    #include <string.h>
    char output[50];
    int yyline;
    #define write fwrite(output, strlen(output), 1, yyout);
%}

%%

\n  yyline++;//contador de linhas
[ \t\n]+    //não faz nada quando encontra espaço

    //operadores algébricos
"+"     sprintf(output, "line: %d token: ALGOP value: +\n", yyline); write;
"-"     sprintf(output, "line: %d token: ALGOP value: -\n", yyline); write;
"*"     sprintf(output, "line: %d token: ALGOP value: *\n", yyline); write;
"/"     sprintf(output, "line: %d token: ALGOP value: /\n", yyline); write;
"||"    sprintf(output, "line: %d token: ALGOP value: OR\n", yyline); write;
"&&"    sprintf(output, "line: %d token: ALGOP value: AND\n", yyline); write;

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
