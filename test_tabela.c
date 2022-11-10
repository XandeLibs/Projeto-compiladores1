#include <stdio.h>
#include <stdlib.h>
#include "tabeladesimbolos.h"

int main(void){
  SymbCateg categ1 = S_VARIABLE;
  SymbCateg categ2 = S_PARAMETER;

  Tabela * tabela = maketabela();
  add(categ1, "test", 1, tabela);
  add(categ2, "test2", 20, tabela);
  display(tabela);
  return 0;
}
