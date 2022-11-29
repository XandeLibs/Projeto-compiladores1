analisador: analisador_lexico.o analisador_sintatico.o tabeladesimbolos.o
	gcc analisador_sintatico.o analisador_lexico.o  tabeladesimbolos.o -o analisador

analisador_lexico.o: analisador_lexico.c analisador_lexico.h
	gcc -c analisador_lexico.c

analisador_sintatico.o: analisador_sintatico.c analisador_sintatico.h
	gcc -c analisador_sintatico.c

tabeladesimbolos.o: tabeladesimbolos.c tabeladesimbolos.h
	gcc -c tabeladesimbolos.c

clean:
	-del -fR *.o