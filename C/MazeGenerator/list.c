#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define NIL -1

typedef struct L_Elem {
  int i;
  int j;
} L_Elem;

typedef struct List {
  int ocup;
  int prElem;
  L_Elem m[];
} List;

void actualRemove(List ** l, int elem);

void L_create(List ** l, size_t listSize) {
  srandom(time(NULL));
  *l = malloc(sizeof(List) + listSize * sizeof(L_Elem));
  (*l)->ocup = 0;
  (*l)->prElem = 0;
  int i;
  L_Elem e;
  e.i = NIL;
  for (i = 0; i<listSize; i++) {
    (*l)->m[i] = e;
  }
}

void L_destroy(List * l) {
  if (l != NULL) {
    free(l);
  }
}

void L_append(List ** l, int i, int j) {
  L_Elem e;
  e.i = i; e.j = j;
  (*l)->m[(*l)->ocup] = e;
  (*l)->ocup = (*l)->ocup + 1; 
}

void L_remove(List ** l, int i, int j) {
  L_Elem *  mem = (*l)->m;
  int prElem = (*l)->prElem;

  if (mem[prElem].i == i && mem[prElem].j == j) {
    actualRemove(l, prElem);
  } else {
    int k;
    int max = (*l)->ocup;
    for(k = 0; k<max; k++) {
      if (mem[k].i == i && mem[k].j == j) {
        actualRemove(l, k);
      }
    }
  }
}

void L_chooseRandom(List ** l, int * i, int * j) {
  int elem = random() % (*l)->ocup-1;
  if (elem < 0) {
    elem = 0;
  }
  
  *i = (*l)->m[elem].i;
  *j = (*l)->m[elem].j;
 
  (*l)->prElem = elem;
}

bool L_isEmpty(List * l) {
  return l->ocup == 0;
}

void actualRemove(List ** l, int elem) {
  (*l)->ocup = (*l)->ocup - 1;
  (*l)->m[elem] = (*l)->m[(*l)->ocup];
}
