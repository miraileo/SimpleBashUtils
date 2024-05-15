#include "s21_cat.h"

void Cat(Flags flags, int argc, char *argv[]) {
  char c;
  int lineNumber = 1;
  int printNumber = 1;
  int numOfEmptyLines = 0;
  FILE *fp = NULL;
  for (int i = optind; i < argc; i++) {
    fp = fopen(argv[i], "r");
    if (fp == NULL) {
      fprintf(stderr, "cat: %s: No such file or directory\n", argv[i]);
      continue;
    }
    while ((c = fgetc(fp)) != EOF) {
      if (printNumber) {
        if (flags.s && c == '\n')
          numOfEmptyLines++;
        else if (flags.s && c != '\n')
          numOfEmptyLines = 0;
        if (flags.s && numOfEmptyLines > 1) continue;
        if (!flags.b && flags.n) {
          printf("%6d\t", lineNumber);
          lineNumber++;
        }
        if (flags.b && c != '\n') {
          printf("%6d\t", lineNumber);
          lineNumber++;
        }
        printNumber = 0;
      }
      if (flags.t || flags.e || flags.v) {
        if ((c < 32 || c == 127) && (c != 9 && c != 10)) {
          putchar('^');
          c = (c + 64) % 128;
        }
      }
      if ((flags.t || flags.T) && c == '\t') {
        printf("^I");
        continue;
      }
      if ((flags.e || flags.E) && ((c == '\n') || (c == '\0'))) {
        putchar('$');
      }
      if (c == '\n') printNumber = 1;
      putchar(c);
    }
    fclose(fp);
  }
}