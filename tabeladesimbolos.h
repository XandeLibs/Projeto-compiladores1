#ifndef TABELA_HEADER
#define TABELA_HEADER

typedef struct _symbEntry SymbEntry;
typedef struct tabela Tabela;
typedef enum {S_CONST = 1, S_VARIABLE, S_PARAMETER, S_FUNCTION, S_LABEL} SymbCateg;
typedef enum {P_VALUE = 1, P_VARIABLE} Passage;

Tabela * maketabela();
void add(SymbCateg categ, char *ident, int data, Tabela * tabela);
void display(Tabela * Tabela);
void destroy(Tabela * Tabela);

#endif
