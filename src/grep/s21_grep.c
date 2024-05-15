#include "s21_grep.h"

int main(int argc, char *argv[]) {
  char *arrayOfFiles[MAX_FILES];
  char *arrayOfPatterns[MAX_PATTERNS];
  int numOfFiles = 0;
  int numOfPatterns = 0;
  int allmatch = 0;
  Flags flags = {0};
  Parser(argc, argv, arrayOfFiles, arrayOfPatterns, &numOfFiles, &numOfPatterns,
         &flags, &allmatch);
  Grep(arrayOfFiles, arrayOfPatterns, numOfFiles, numOfPatterns, flags,
       allmatch);
  return 0;
}