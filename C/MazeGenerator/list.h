#include <stdbool.h>
typedef struct List List;

void L_create(List ** l, size_t listSize);
void L_destroy(List * l);
void L_append(List ** l, int i, int j);
void L_remove(List ** l, int i, int j);
void L_chooseRandom(List ** l, int * i, int * j);
bool L_isEmpty(List * l);
