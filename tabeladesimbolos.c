#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "tabeladesimbolos.h"

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

SymbEntry * createSymbEntry(SymbCateg categ, char *ident, int level){
  SymbEntry * newSymbEntry = malloc(sizeof(SymbEntry));
  if (!newSymbEntry) {
    return NULL;
  }
  newSymbEntry->categ = categ;
  newSymbEntry->ident = ident;
  newSymbEntry->level = level;
  newSymbEntry->next = NULL;
  return newSymbEntry;
}

Tabela * maketabela(){
  Tabela * tabela = malloc(sizeof(Tabela));
  if (!tabela) {
    return NULL;
  }
  tabela->head = NULL;
  return tabela;
}

void display(Tabela * tabela) {
  SymbEntry * current = tabela->head;
  if(tabela->head == NULL) 
    return;
  
  for(; current != NULL; current = current->next) {
    printf("%d\n", current->categ);
    printf("%s\n", current->ident);
    printf("%d\n", current->level);
  }
}

void addConstant(char *ident, int level, Tabela * tabela, int value, TypeDescrPtr type){
  SymbEntry* entry;
  entry = add(S_CONST, ident, level, tabela);
  entry->descr.c.value = value;
  entry->descr.c.type = type;
}

void addVariable(char *ident, int level, Tabela * tabela, int displ, TypeDescrPtr type){
  SymbEntry* entry;
  entry = add(S_VARIABLE, ident, level, tabela);
  entry->descr.v.displ = displ;
  entry->descr.v.type = type;
}

void addFormal_Param(char *ident, int level, Tabela * tabela, int displ, TypeDescrPtr type, Passage pass){
  SymbEntry* entry;
  entry = add(S_PARAMETER, ident, level, tabela);
  entry->descr.fm.displ = displ;
  entry->descr.fm.type = type;
  entry->descr.fm.pass = pass;
}

void addFunction(char *ident, int level, Tabela * tabela, int displ, TypeDescrPtr result, SymbEntry *params){
  SymbEntry* entry;
  entry = add(S_FUNCTION, ident, level, tabela);
  entry->descr.f.displ = displ;
  entry->descr.f.result = result;
  entry->descr.f.params = params;
}

void addLabel(char *ident, int level, Tabela * tabela, char *label, bool defined){
  SymbEntry* entry;
  entry = add(S_LABEL, ident, level, tabela);
  entry->descr.l.label = label;
  entry->descr.l.defined = defined;
}

TypeDescrPtr addType(char *ident, int level, Tabela * tabela, TypeConstr predef_function, int size){
  SymbEntry* entry;
  entry = add(S_TYPE, ident, level, tabela);
  TypeDescr *description = malloc(sizeof(TypeDescr));
  description->constr = predef_function;
  description->size = size;
  entry->descr.t.type = description;
  
  return description;
}

SymbEntry* add(SymbCateg categ, char *ident, int level, Tabela * tabela){
  SymbEntry * current = NULL;
  if(tabela->head == NULL){
    tabela->head = createSymbEntry(categ, ident, level);
    return tabela->head;
  }
  else {
    current = tabela->head; 
    while (current->next!=NULL){
      current = current->next;
    }
    current->next = createSymbEntry(categ, ident, level);
    return current->next;
  }
}

//retorna NULL caso não ache o simbolo
SymbEntry* search(SymbCateg categ, char *ident, Tabela * tabela){
  SymbEntry* procura = tabela->head;

  while(procura != NULL && strcmp(procura->ident, ident) != 0 && procura->categ != categ){
    procura = procura->next;
  }

  return procura;
}

//retorna o descritor de tipo da entry symb
TypeDescrPtr getType(SymbEntry* symb){
  return symb->descr.t.type;
}

void destroy(Tabela * tabela){
  SymbEntry * current = tabela->head;
  SymbEntry * next = current;
  while(current != NULL){
    next = current->next;
    free(current);
    current = next;
  }
  free(tabela);
}
