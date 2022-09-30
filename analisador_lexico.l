%{
    #include <stdio.h>
    #include <string.h>
    #include <ctype.h>
    #include "linkedlist.c"

    FILE *fileIn, *fileOut, *fileInLowerCase;
    char output[50];
    int a, yyline;
    node *LISTA_DE_SIMBOLOS = NULL;
%}

/*Definições macros*/
digit [0-9]
integer {digit}+
identifier [a-zA-Z][a-zA-Z0-9]*

%%

\n  yyline++;/*contador de linhas*/
[ \t]+ ;   /*não faz nada quando encontra espaço*/

        /*Identificando as palavras reservadas*/ 
integer|boolean|true|false|read|write|void|while|if|return|goto|types|functions|labels|vars|var|else {sprintf(output, "line: %d token: KEY value: %s\n", yyline, yytext); fwrite(output, strlen(output), 1, yyout);;} 

        /*operadores de adição*/
"+"     sprintf(output, "line: %d token: ADDOP value: +\n", yyline); fwrite(output, strlen(output), 1, yyout);
"-"     sprintf(output, "line: %d token: ADDOP value: -\n", yyline); fwrite(output, strlen(output), 1, yyout);
"||"    sprintf(output, "line: %d token: ADDOP value: OR\n", yyline); fwrite(output, strlen(output), 1, yyout);

        /*operadores de multiplicação*/
"*"     sprintf(output, "line: %d token: MULOP value: *\n", yyline); fwrite(output, strlen(output), 1, yyout);
"/"     sprintf(output, "line: %d token: MULOP value: /\n", yyline); fwrite(output, strlen(output), 1, yyout);
"&&"    sprintf(output, "line: %d token: MULOP value: AND\n", yyline); fwrite(output, strlen(output), 1, yyout);

        /*Simbolos simples*/
"!"    sprintf(output, "line: %d token: NOT\n", yyline); fwrite(output, strlen(output), 1, yyout);
";"    sprintf(output, "line: %d token: SEMICOLON\n", yyline); fwrite(output, strlen(output), 1, yyout);
"="    sprintf(output, "line: %d token: ASSIGN\n", yyline); fwrite(output, strlen(output), 1, yyout);
":"    sprintf(output, "line: %d token: COLON\n", yyline); fwrite(output, strlen(output), 1, yyout);
","    sprintf(output, "line: %d token: COMMA\n", yyline); fwrite(output, strlen(output), 1, yyout);
"{"    sprintf(output, "line: %d token: LCB\n", yyline); fwrite(output, strlen(output), 1, yyout);
"}"    sprintf(output, "line: %d token: RCB\n", yyline); fwrite(output, strlen(output), 1, yyout);
"["    sprintf(output, "line: %d token: LB\n", yyline); fwrite(output, strlen(output), 1, yyout);
"]"    sprintf(output, "line: %d token: RB\n", yyline); fwrite(output, strlen(output), 1, yyout);
"("    sprintf(output, "line: %d token: LP\n", yyline); fwrite(output, strlen(output), 1, yyout);
")"    sprintf(output, "line: %d token: RP\n", yyline); fwrite(output, strlen(output), 1, yyout);

        /*Adicionar constantes e ID*/
{integer}               sprintf(output, "line: %d token: CONST value: %s\n", yyline, yytext); fwrite(output, strlen(output), 1, yyout);
{identifier}+           sprintf(output, "line: %d token: ID value: %s\n", yyline, yytext); fwrite(output, strlen(output), 1, yyout); add(LISTA_DE_SIMBOLOS, yytext);
                        

        /*Adicionar operadores relacionais*/ 
"=="    sprintf(output, "line: %d token: RELOP value: EQ\n", yyline); fwrite(output, strlen(output), 1, yyout);
"!="    sprintf(output, "line: %d token: RELOP value: NEQ\n", yyline); fwrite(output, strlen(output), 1, yyout);
"<"     sprintf(output, "line: %d token: RELOP value: LT\n", yyline); fwrite(output, strlen(output), 1, yyout);
">"     sprintf(output, "line: %d token: RELOP value: GT\n", yyline); fwrite(output, strlen(output), 1, yyout);
"<="    sprintf(output, "line: %d token: RELOP value: LEQ\n", yyline); fwrite(output, strlen(output), 1, yyout);
">="    sprintf(output, "line: %d token: RELOP value: GEQ\n", yyline); fwrite(output, strlen(output), 1, yyout);

%%

int yywrap(void){
    return 1;
}

int main(int argc, char const *argv[]){
    if(argc > 1){
        if(!strcmp(argv[1],"--help")){
            printf("Analisador Lexico para a linguagem Amaury++\nUso: Compilador <arquivo txt de entrada> [<arquivo txt de saida>]\n");
            return 0;
        }
        else{
            char *fext = strrchr(argv[1], '.');
            if(fext && !strcmp(fext, ".txt")){
                fileIn = fopen(argv[1], "r");
            }
            else{
                printf("O arquivo de entrada deve ter a extensao txt\n");
                return 0;
            }
            
            if(argc > 2){
                fext = strrchr(argv[2], '.');
                if(fext && !strcmp(fext, ".txt")){
                    yyout = fopen(argv[2], "w");
                }
                else{
                    printf("O arquivo de saida deve ter a extensao txt\n");
                    return 0;
                }
            }
            else
                yyout = fopen("out.txt", "w");
        }
    }
    else{
        printf("Uso indevido: Arquivo de entrada faltando\n");
        return 0;
    }
    fileInLowerCase=fopen("in-lowercase.txt","w+"); 

    /* Converte arquivo de entrada para letras minusculas */
    while ((a = fgetc(fileIn)) != EOF) {
            a = tolower(a);
            fputc(a, fileInLowerCase);
    };

    rewind(fileInLowerCase);

    yyin = fileInLowerCase;
    yylex();
    display_list(LISTA_DE_SIMBOLOS);
    fclose(fileIn);
    fclose(fileInLowerCase);
    fclose(yyout);
    free_list(LISTA_DE_SIMBOLOS);

    return 0;
}
