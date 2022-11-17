#ifndef TABELA_HEADER
#define TABELA_HEADER
#include <stdbool.h>

typedef struct _Constant {
  int value;
  TypeDescrPtr type;
} Constant;

typedef struct _Variable {
  int displ;
  TypeDescrPtr type;
} Variable;

typedef struct _Formal_Pam {
  int displ;
  TypeDescrPtr type;
  Passage pass;
} Formal_Pam;

typedef struct _Function {
  int displ;
  TypeDescrPtr result;
  SymbEntry *params;
} Function;

typedef struct _Label {
  char *label;
  bool defined;
} Label;

typedef struct _Type {
  TypeDescrPtr type;
} Type;

typedef struct _symbEntry {
  SymbCateg categ;
  char *ident;
  int level;
  struct _symbEntry * next;

  union {
    Constant c;
    Variable v;
    Formal_Pam fm;
    Function f;
    Label l;
    Type t;
  } descr;
}SymbEntry;

typedef struct tabela {
  SymbEntry * head; 
}Tabela;

typedef struct _TypeDescr {
  TypeConstr constr;
  int size;
}*TypeDescrPtr, TypeDescr;

typedef enum {S_CONST = 1, S_VARIABLE, S_PARAMETER, S_FUNCTION, S_LABEL, S_TYPE} SymbCateg;
typedef enum {P_VALUE = 1, P_VARIABLE} Passage;
typedef enum {T_PREDEF = 1, T_FUNCTION } TypeConstr;

Tabela * maketabela();
SymbEntry * createSymbEntry(SymbCateg categ, char *ident, int level);
void addConstant(char *ident, int level, Tabela * tabela, int value, TypeDescrPtr type);
void addVariable(char *ident, int level, Tabela * tabela, int displ, TypeDescrPtr type);
void addFormal_Param(char *ident, int level, Tabela * tabela, int displ, TypeDescrPtr type, Passage pass);
void addFunction(char *ident, int level, Tabela * tabela, int displ, TypeDescrPtr result, SymbEntry *params);
void addLabel(char *ident, int level, Tabela * tabela, char *label, bool defined);
TypeDescrPtr addType(char *ident, int level, Tabela * tabela, TypeConstr predef_function, int size);
SymbEntry* add(SymbCateg categ, char *ident, int data, Tabela * tabela);
void display(Tabela * Tabela);
SymbEntry* search(SymbCateg categ, char *ident, Tabela * tabela);
void destroy(Tabela * Tabela);

#endif
