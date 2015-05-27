#include <string.h>

#include "a_sint.h"

/*
 * No s'ha agegit cap funcio matematica
 * http://stackoverflow.com/questions/7951019/convert-string-to-float sam answer << Revisar
 * Falta afegir les produccions extra i tokens per la potencia a mes del que calgui
 * Si s'afegeixen moltes funcionalitats, considerar pasar a un parser ascendent
 * Optimitzar fent que es processi l'input cada cop que un simbol no digit tengui igual o menor precedencia que
 * el darrer simbol no digit aparegut (de cara a la GUI)
 * Optimitzar l'analitzador lexic:
 * -> la conversio de char a num, fer-la amb una func estandar emprant el
 *    substring pertinent, seria mes optim? << Revisio important -> optimitzacio
 * -> convertir-lo en un DFA parcial
 */

void print(char * input, double res) {
  char a [100];
  int i;
  snprintf(a,100, "%f", res);
  i = strlen(a) - 1;
  while(a[i] == '0' && i > 0) {
    i--;
  }
  if(a[i] == '.') {
    i--;
  }
  // +1 perq l'index comença a 0 i +1 per el \0
  i += 2;
  char sres [i];
  snprintf(sres,i,"%s",a);
  printf("%s%s\n",input,sres);
}

int main (int argc, char * argv []) {
  char * input;
  if (argc == 2) {
    input = argv[1];
  } else {
    printf("Usage: ./calc \"mathematical expression to evaluate\"\n\tCurrently only +,-,*,/ with or without parenthesis are accepted.\n\tBoth integer and floating point expressions are acceptable.\n");
    return -1;
  }
  print(input, a_sint(input));
  return 0;
}
