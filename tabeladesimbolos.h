#ifndef TABELA_HEADER
#define TABELA_HEADER
#include <stdbool.h>

typedef struct _symbEntry SymbEntry;
typedef struct tabela Tabela;
typedef struct _TypeDescr *TypeDescrPtr;
typedef struct _TypeDescr TypeDescr;
typedef enum {S_CONST = 1, S_VARIABLE, S_PARAMETER, S_FUNCTION, S_LABEL, S_TYPE} SymbCateg;
typedef enum {P_VALUE = 1, P_VARIABLE} Passage;
typedef enum {T_PREDEF = 1, T_FUNCTION } TypeConstr;

Tabela * maketabela();
SymbEntry * createSymbEntry(SymbCateg categ, char *ident, int level);
void addConstant(SymbCateg categ, char *ident, int level, Tabela * tabela, int value, TypeDescrPtr type);
void addVariable(SymbCateg categ, char *ident, int level, Tabela * tabela, int displ, TypeDescrPtr type);
void addFormal_Param(SymbCateg categ, char *ident, int level, Tabela * tabela, int displ, TypeDescrPtr type, Passage pass);
void addFunction(SymbCateg categ, char *ident, int level, Tabela * tabela, int displ, TypeDescrPtr result, SymbEntry *params);
void addLabel(SymbCateg categ, char *ident, int level, Tabela * tabela, char *label, bool defined);
TypeDescrPtr addType(SymbCateg categ, char *ident, int level, Tabela * tabela, TypeConstr predef_function, int size);
SymbEntry* add(SymbCateg categ, char *ident, int data, Tabela * tabela);
void display(Tabela * Tabela);
SymbEntry* search(SymbCateg categ, char *ident, Tabela * tabela);
void destroy(Tabela * Tabela);

#endif
