analisador: lex.c
	gcc lex.yy.c -o $@
lex.c: analisador_lexico.l
	flex analisador_lexico.l