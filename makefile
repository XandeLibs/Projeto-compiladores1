analisador: lex yacc
	gcc lex.yy.c y.tab.c -o $@
lex: analisador_lexico.l
	flex analisador_lexico.l
yacc: analisador_sintatico.y
	bison -dy analisador_sintatico.y