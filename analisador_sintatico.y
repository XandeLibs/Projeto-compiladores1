%{
int yylex(void);
int yyerror(const char *s);
%}

%union {int num; char id; char op;}
%token <op> ADDOP
%token <op> MULOP
%token NOT
%token SEMICOLON
%token ASSIGN
%token COLON
%token COMMA
%token LCB
%token RCB
%token LB
%token RB
%token LP
%token RP
%token <num> INT
%token <id> ID
%token RELOP

%start program

%%

program : function;

function : ID ID formal_parameters block
        | 'void' ID formal_parameters block
        ;
block : body
        | labels body
        | types body
        | variables body
        | functions body
        | labels types body
        | labels variables body
        | labels functions body
        | types variables body
        | types functions body
        | variables functions body
        | labels types variables body
        | labels types functions body
        | labels variables functions body
        | types variables functions body
        | labels types variables functions body
        ;

labels : 'labels' identifier_list;

types : 'types' types1;

types1 : types1 ID ASSIGN type SEMICOLON
		| ID ASSIGN type SEMICOLON
		;

variables : 'vars' variables1;

variables1 : variables1 identifier_list COLON type SEMICOLON
			| identifier_list COLON type SEMICOLON
			;

functions : 'functions' functions1;

functions1 : functions1 function
			| function
			;

body : LCB body1 RCB;

body1 : body1 statement
		| 
		;

type : ID type1;

type1 : type1 LB INT RB;
		| 
		;

formal_parameters : LP formal_parameter formal_parameters1 RP;
                    | LP RP
                    ;

formal_parameters1 : formal_parameters1 SEMICOLON formal_parameter
					| 
					;

formal_parameter : expression_paramenter
                    | function_parameter
                    ;

expression_paramenter : 'var' identifier_list COLON ID
						| identifier_list COLON ID
						;

function_parameter : ID ID formal_parameters
					| 'void' ID formal_parameters
					;

statement : ID COLON unlabeled_statement
			| unlabeled_statement 
			| compound
			;

variable : ID variable1; 

variable1 : variable1 LB expression RB
			| 
			;

unlabeled_statement : assignement
					| function_call_statement
					| goto
					| return
					| conditional
					| repetitive
					| empty_statement
					;

assignement : variable ASSIGN expression SEMICOLON;

function_call_statement : function_call SEMICOLON;

goto : 'goto' ID SEMICOLON;

return : 'return' SEMICOLON
		| 'return' expression SEMICOLON
		;

compound : LCB compound1 RCB;

compound1 : compound1 unlabeled_statement
			| unlabeled_statement
			;

conditional : 'if' LP expression RP compound
			| 'if' LP expression RP compound 'else' compound;

repetitive : 'while' LP expression RP compound;

empty_statement : SEMICOLON;

expression : simple_expression 
			| simple_expression RELOP simple_expression
			;

simple_expression : '+' term simple_expression1
					| '-' term simple_expression1
					| term simple_expression1
					;

simple_expression1 : ADDOP term simple_expression1
					| 
					;

term : factor term1;

term1 : term1 MULOP factor
		| 
		;

factor : variable
		| 'integer'
		| function_call
		| LP expression RP
		| NOT factor
		;

function_call : ID LP expression_list RP;

identifier_list : ID identifier_list1;

identifier_list1 : identifier_list1 COMMA ID
				| 
				;

expression_list : expression expression_list1
				| 
				;

expression_list1 : expression_list1 COMMA expression
				| 
				;

%%
