#include <stdbool.h>

typedef enum Token {
  tk_fi, tk_err, tk_sum, tk_res, tk_prd, tk_quo, tk_mod, tk_par_ob, tk_par_tanc, tk_lit
} Token;

static const char tokenVal[] = {'=','e','+','-','*','/','%','(',')','i'};
// variable emprada per debuguejar
//static const char * tokenMap[] = {"fi", "error", "suma", "resta", "producte", "quocient", "modul","par_o", "par_t", "lit"};
