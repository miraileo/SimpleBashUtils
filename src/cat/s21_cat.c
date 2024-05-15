#include "s21_cat.h"

int main(int argc, char *argv[]) {
  Flags flags = {0};
  Parser(argc, argv, &flags);
  Cat(flags, argc, argv);
  return 0;
}