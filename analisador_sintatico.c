#include <stdio.h>
#include <stdlib.h>
#include "analisador_lexico.h"
#include "analisador_sintatico.h"

int lookahead;
FILE *fin;
bool correto = true;

/* Exige que o próximo terminal seja t e avança o ponteiro da fita de entrada (i.e., pega o próximo terminal) */
void match(int t)
{
    //printf("Linha:%d: Encontrou %s com valor %d, procura %d\n", lines, lexema, lookahead, t);

    if(lookahead == ERRO_LEXICO){
        printf("Erro lexico, \"%s\" na linha %d nao faz parte da linguagem\n", lexema, lines);
        exit(-1);
    }
    else if(lookahead == t){
        lookahead = lex();
    }
    else{
        printf("\nErro(linha=%d): token %s esperado. Encontrado \"%s\"\n", lines, terminais[t], lexema);
        correto = false;
        lookahead = lex();
    }
}

// program -> function
void program(){
    function();
}

// function -> ID ID formal_parameters block
//           | VOID ID formal_parameters block
void function(){
    if(lookahead == ID){
        match(ID);
    }
    else{
        match(VOID);
    }
    match(ID);
    formal_parameters();
    block();
}

// block -> body
//        | labels body
//        | variables body
//        | functions body
//        | labels variables body
//        | labels functions body
//        | variables functions body
//        | labels variables functions body
void block(){
    if(lookahead == LABELS){
        labels();
    }
    if(lookahead == VARS){
        variables();
    }
    if(lookahead == FUNCTIONS){
        functions();
    }
    body();
}

// labels -> LABELS identifier_list SEMICOLON
void labels(){
    match(LABELS);
    identifier_list();
    match(SEMICOLON);
}

// variables -> VARS identifier_list COLON type SEMICOLON variables_
void variables(){
    match(VARS);
    identifier_list();
    match(COLON);
    type();
    match(SEMICOLON);
    variables_();
}

// variables_ -> identifier_list COLON type SEMICOLON variables_
//             | epsilon
void variables_(){
    if(lookahead == ID){
        identifier_list();
        match(COLON);
        type();
        match(SEMICOLON);
        variables_();
    }
}

// functions -> FUNCTIONS function functions_
void functions(){
    match(FUNCTIONS);
    function();
    functions_();
}

// functions_ -> function functions_
//             | epsilon
void functions_(){
    if(lookahead == ID || lookahead == VOID){
        function();
        functions_();
    }
}

// body -> LCB body_ RCB
void body(){
    match(LCB);
    body_();
    match(RCB);
}

// body_ -> statement body_
//        | epsilon
void body_(){
    if(lookahead == ID || lookahead == GOTO || lookahead == RETURN || lookahead == IF || lookahead == WHILE || lookahead == SEMICOLON || lookahead == LCB){
        statement();
        body_();
    }
}

//type -> ID
void type(){
    match(ID);
}

// formal_parameters -> LP formal_parameter formal_parameters_ RP
//                    | LP RP
void formal_parameters(){
    match(LP);
    if(lookahead == VAR || lookahead == ID){
        formal_parameter();
        formal_parameters_();
    }
    match(RP);
}

// formal_parameters_ -> SEMICOLON formal_parameter formal_parameters_
//                     | epsilon
void formal_parameters_(){
    if(lookahead == SEMICOLON){
        match(SEMICOLON);
        formal_parameter();
        formal_parameters_();
    }
}

// formal_parameter -> expression_parameter
void formal_parameter(){
    expression_parameter();
}

// expression_parameter -> var identifier_list : ID
//                       | identifier_list : ID
void expression_parameter(){
    if(lookahead == VAR){
        match(VAR);
    }
    identifier_list();
    match(COLON);
    match(ID);
}

// statement -> compound
//            | unlabeled_statement
//            | ID statement_
void statement(){
    if(lookahead == LCB){
        compound();
    }
    else if(lookahead == ID){
        match(ID);
        statement_();
    }
    else{
        unlabeled_statement();
    }
}

// statement_ -> : unlabeled_statement
//             | unlabeled_statement_
void statement_(){
    if(lookahead == COLON){
        match(COLON);
        unlabeled_statement();
    }
    else{
        unlabeled_statement_();
    }
}

// unlabeled_statement -> ID unlabeled_statement_
//                      | GOTO
//                      | RETURN
//                      | conditional
//                      | repetitive
//                      | SEMICOLON
void unlabeled_statement(){
    if(lookahead == ID){
        match(ID);
        unlabeled_statement_();
    }
    else if(lookahead == GOTO){
        _goto();
    }
    else if(lookahead == RETURN){
        _return();
    }
    else if(lookahead == IF){
        conditional();
    }
    else if(lookahead == WHILE){
        repetitive();
    }
    else {
        match(SEMICOLON);
    }
}

// unlabeled_statement_ -> function_call SEMICOLON
//                       | assignement
void unlabeled_statement_(){
    if(lookahead == LP){
        function_call();
        match(SEMICOLON);
    }
    else{
        assignment();
    }
}

// assignment -> ASSIGN expression SEMICOLON
void assignment(){
    match(ASSIGN);
    expression();
    match(SEMICOLON);
}

// _goto -> GOTO ID SEMICOLON
void _goto(){
    match(GOTO);
    match(ID);
    match(SEMICOLON);
}

// _return -> RETURN SEMICOLON
//          | RETURN expression SEMICOLON
void _return(){
    match(RETURN);
    if(lookahead == SEMICOLON){
        match(SEMICOLON);
    }
    else{
        expression();
        match(SEMICOLON);
    }
}

// compound -> LCB unlabeled_statement compound_ RCB
void compound(){
    match(LCB);
    unlabeled_statement();
    compound_();
    match(RCB);
}

// compound_ -> unlabeled_statement compound_
//            | epsilon
void compound_(){
    if(lookahead == ID || lookahead == GOTO || lookahead == RETURN || lookahead == IF || lookahead == WHILE || lookahead == SEMICOLON){
        unlabeled_statement();
        compound_();
    }
}

// conditional -> IF LP expression RP compound conditional_
void conditional(){
    match(IF);
    match(LP);
    expression();
    match(RP);
    compound();
    conditional_();
}

// conditional_ -> ELSE compound
//               | epsilon
void conditional_(){
    if(lookahead == ELSE){
        match(ELSE);
        compound();
    }
}

// repetitive -> WHILE LP expression RP compound
void repetitive(){
    match(WHILE);
    match(LP);
    expression();
    match(RP);
    compound();
}

// expression -> simple_expression
//             | simple_expression RELOP simple_expression
void expression(){
    simple_expression();
    if(lookahead == RELOP){
        match(RELOP);
        simple_expression();
    }
}



// simple_expression -> ADDOP term simple_expression_
//                    | term simple_expression_
void simple_expression(){
    if(lookahead == ADDOP){
        match(ADDOP);
    }
    term();
    simple_expression_();
}

// simple_expression_ -> ADDOP term simple_expression_
//                     | OR term simple_expression_
//                     | epsilon
void simple_expression_(){
    if(lookahead == ADDOP){
        match(ADDOP);
        term();
        simple_expression_();
    }
    else if(lookahead == OR){
        match(OR);
        term();
        simple_expression_();
    }
}

// term -> factor term_
void term(){
    factor();
    term_();
}

// term_ -> MULOP factor term_
//        | epsilon
void term_(){
    if(lookahead == MULOP){
        match(MULOP);
        factor();
        term_();
    }
}

// factor -> ID factor_
//         | CONST
//         | LP expression RP
//         | NOT factor
void factor(){
    if(lookahead == ID){
        match(ID);
        factor_();
    }
    else if(lookahead == CONST){
        match(CONST);
    }
    else if(lookahead == LP){
        match(LP);
        expression();
        match(RP);
    }
    else if(lookahead == NOT){
        match(NOT);
        factor();
    }
}

// factor_ -> function_call
//          | epsilon
void factor_(){
    if(lookahead == LP){
        function_call();
    }
}

// function_call -> ID LP expression_list RP
void function_call(){
    match(LP);
    expression_list();
    match(RP);
}

// identifier_list -> ID identifier_list_
void identifier_list(){
    match(ID);
    identifier_list_();
}

// identifier_list_ -> COMMA ID identifier_list_
//                   | epsilon
void identifier_list_(){
    if(lookahead == COMMA){
        match(COMMA);
        match(ID);
        identifier_list_();
    }
}

// expression_list -> expression expression_list_
//                  | epsilon
void expression_list(){
    if(lookahead == ADDOP || lookahead == ID || lookahead == CONST || lookahead == LP || lookahead == NOT){
        expression();
        expression_list_();
    } 
}

// expression_list_ -> COMMA expression expression_list_
//                   | epsilon
void expression_list_(){
    if(lookahead == COMMA){
        match(COMMA);
        expression();
        expression_list_();
    }
}

char *parser()
{
    Tabela * simbolos;
    simbolos = maketabela();
    TypeDescrPtr type_boolean;
    //adiciona funções, tipos e constantes pré definidas da linguagem
    addFunction(S_FUNCTION, "read", -1, simbolos, 0, NULL, createSymbEntry(S_PARAMETER, "r1", 0));
    addFunction(S_FUNCTION, "write", -1, simbolos, 0, NULL, createSymbEntry(S_PARAMETER, "w1", 0));
    addType(S_TYPE, "integer", 0, simbolos, 0, 4);
    type_boolean = addType(S_TYPE, "boolean", 0, simbolos, 0, 1);
    addConstant(S_CONST, "false", -1, simbolos, 0, type_boolean);
    addConstant(S_CONST, "true", -1, simbolos, 1, type_boolean);

    lookahead = lex(); // inicializa lookahead com o primeiro terminal da fita de entrada (arquivo)
    program(); // chama a variável inicial da gramática.

    if(lookahead==FIM_ARQ){
        if(correto)
        return("Programa sintaticamente correto!");
    }
    else
        return("Fim de arquivo esperado");
}

int main(int argc, char**argv)
{

    if(argc<2){
        printf("\nUso: analisador <nome do arquivo>\n");
        return 1;
    }
    else{
        fin = fopen(argv[1], "r");
        if(!fin){
            printf("\nProblema na abertura do programa %s\n", argv[1]);
            return 1;
        }
        // chama o parser para processar o arquivo de entrada
        printf("\nResultado: %s\n", parser());
        fclose(fin);
        return 0;
    }
}
