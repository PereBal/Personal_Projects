#include "a_sint.h"

double a_E();
double a_T();
double a_F();

Token tk;

bool acc(Token token) {
  return tk == token;
}

void error() {
  fprintf(stderr,"Unexpected simbol '%c' \n", Etok());
  exit(-1);
}

void errno(char * str) {
  fprintf(stderr,str);
  exit(-1);
}

double calcula (Token tk, double a, double b) {
  switch(tk) {
    case tk_sum:
      return a + b;
      break;
    case tk_res:
      return a - b;
      break;
    case tk_prd:
      return a * b;
      break;
    case tk_quo:
      return a / b;
      break;
    case tk_mod:
      error("L'operacio modul esta temporalment inhabilitada!");
      return (double)((int)a % (int)b);
      break;
    default:
      error();
      // statement never reached
      return -1;
  }
}

double a_F() {
  double res = -1;
  if(acc(tk_lit)) {
    res = Lval();
    tk = llegeix();
  } else if(acc(tk_par_ob)) {
    tk = llegeix();
    res = a_E();
    if(acc(tk_par_tanc)) {
      tk = llegeix();
    } else {
      error();
    }
  } else {
    error();
  }
  return res;
}

double a_T() {
  Token ltk;
  double res, lval;
  res = a_F();
  while (acc(tk_prd) || acc(tk_quo)) {
    ltk = tk;
    tk = llegeix();
    lval = a_F();
    res = calcula(ltk, res, lval);
  }
  return res;
}

double a_E() {
  Token ltk;
  double res, lval;
  // unary '-'
  if (tk == tk_res) {
    tk = llegeix();
    res = -a_T();
  } else {
    // unary '+'
    if (tk == tk_sum) {
      tk = llegeix();
    }
    res = a_T();
  }
  while (acc(tk_sum) || acc(tk_res)) {
    ltk = tk;
    tk = llegeix();
    lval = a_T();
    res = calcula(ltk, res, lval);
  }
  return res;
}

double a_sint(char * fn) {
  double res;

  Open_Input(fn);
  tk = llegeix();
  res = a_E();
  Close_Input();

  if (tk != tk_fi) {
    errno("Missing terminal Simbol '='");
  }
  return res;
}
