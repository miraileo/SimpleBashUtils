#include "s21_cat.h"

void Parser(int argc, char *argv[], Flags *flags) {
  int opt;
  while ((opt = getopt(argc, argv, "tesnbvET")) != -1) {
    switch (opt) {
      case 't':
        flags->t = 1;
        break;
      case 'e':
        flags->e = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 'b':
        flags->b = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      case 'E':
        flags->E = 1;
        break;
      case 'T':
        flags->T = 1;
        break;
    }
  }
}