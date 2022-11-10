#ifndef TABELA_HEADER
#define TABELA_HEADER

typedef struct _symbEntry SymbEntry;
typedef struct tabela Tabela;
typedef enum {S_CONST = 1, S_VARIABLE, S_PARAMETER, S_FUNCTION, S_LABEL} SymbCateg;
typedef enum {P_VALUE = 1, P_VARIABLE} Passage;

Tabela * maketabela();
void addConstant(SymbCateg categ, char *ident, int level, Tabela * tabela, int value, TypeDescrPtr type);
void addVariable(SymbCateg categ, char *ident, int level, Tabela * tabela, int displ, TypeDescrPtr type);
void addFormal_Param(SymbCateg categ, char *ident, int level, Tabela * tabela, int displ, TypeDescrPtr type, Passage pass);
void addFunction(SymbCateg categ, char *ident, int level, Tabela * tabela, int displ, TypeDescrPtr result, SymbEntry *params);
void addLabel(SymbCateg categ, char *ident, int level, Tabela * tabela, char *label, bool defined);
SymbEntry* add(SymbCateg categ, char *ident, int data, Tabela * tabela);
void display(Tabela * Tabela);
void destroy(Tabela * Tabela);

#endif
