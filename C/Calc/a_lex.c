#include "a_lex.h"

long ofst = 0;
long * offset = &ofst;
char * s;
double lval = -1;
char etok;
Token ctk;

char firstc() {
  return *(s + *offset);
}

char nextc() {
  *offset = *offset+1;
  return *(s + *offset);
}

Token llegeix() {
  bool end = false;
  char c = firstc();
  while(!end) {
    end = true;
    switch(c) {
      case '+':
        ctk = tk_sum;
        break;
      case '-':
        ctk = tk_res;
        break;
      case '*':
        ctk = tk_prd;
        break;
      case '/':
        ctk = tk_quo;
        break;
      case '%':
        ctk = tk_mod;
        break;
      case '(':
        ctk = tk_par_ob;
        break;
      case ')':
        ctk = tk_par_tanc;
        break;
      case ' ':
        end = false;
        break;
      case '=':
        ctk = tk_fi;
        break;
      default:
        if(c >= '0' && c <= '9') {
          lval = 0;
          while(c >= '0' && c <= '9') {
            lval += (c - '0');
            lval *= 10;
            c = nextc();
          }
          lval /= 10;
          if (c == '.') {
            double fact = 10;
            c = nextc();
            while(c >= '0' && c <= '9') {
              lval += ((c - '0') / fact);
              fact *= 10;
              c = nextc();
            }
          }
          ctk = tk_lit;
          return ctk;
        } else {
          ctk = tk_err;
          etok = c;
        }
    }
    c = nextc();
  }
  return ctk;
}

void Open_Input(char * fn) {
  s = fn;
}

void Close_Input() {

}

char Etok() {
  return etok;
}

double Lval() {
  return lval;
}
