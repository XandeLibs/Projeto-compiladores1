#include <stdio.h>
#include <stdlib.h>
#include "tabeladesimbolos.h"
#include <stdbool.h>

struct _symbEntry {
  SymbCateg categ;
  char *ident;
  int level;
  struct _symbEntry * next;

  union {
    int value;
    int displ;
    char *label;
    bool defined;
    Passage pass;
  } descr;
};

struct tabela {
  SymbEntry * head; 
};

SymbEntry * createSymbEntry(SymbCateg categ, char *ident, int level);

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

void add(SymbCateg categ, char *ident, int level, Tabela * tabela){
  SymbEntry * current = NULL;
  if(tabela->head == NULL){
    tabela->head = createSymbEntry(categ, ident, level);
  }
  else {
    current = tabela->head; 
    while (current->next!=NULL){
      current = current->next;
    }
    current->next = createSymbEntry(categ, ident, level);
  }
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
