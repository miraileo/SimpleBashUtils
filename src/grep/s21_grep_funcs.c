#include "s21_grep.h"

void Grep(char *arrayOfFiles[], char *arrayOfPatterns[], int numOfFiles,
          int numOfPatterns, Flags flags, int allmatch) {
  regex_t regex;
  for (int i = 0; i < numOfFiles; i++) {
    FILE *file = fopen(arrayOfFiles[i], "r");
    if (file == NULL) {
      if (!flags.s)
        fprintf(stderr, "grep: %s: No such file or directory\n",
                arrayOfFiles[i]);
      continue;
    }
    char line[MAX_LINE_LENGTH];
    int numOfLines = 0;
    int count = 0;
    int flag = 0;
    size_t newlinePosition = 0;
    size_t lineLength = 0;
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
      lineLength = strlen(line);
      newlinePosition = strcspn(line, "\n");
      int numOfPatternsInLine = 0;
      numOfLines++;
      for (int j = 0; j < numOfPatterns; j++) {
        if (flags.i)
          regcomp(&regex, arrayOfPatterns[j], REG_EXTENDED | REG_ICASE);
        else
          regcomp(&regex, arrayOfPatterns[j], REG_EXTENDED | REG_NEWLINE);
        if (regexec(&regex, line, 0, 0, 0) == 0) numOfPatternsInLine++;
        regfree(&regex);
      }
      if (((flags.v && numOfPatternsInLine != 0) ||
           (!flags.v && numOfPatternsInLine == 0)) &&
          !allmatch)
        continue;
      if (allmatch && flags.v) flag = 1;
      if (!flag)
        OutputNFlag(flags, numOfFiles, arrayOfFiles, i, numOfLines, line,
                    newlinePosition, lineLength);
      count++;
    }
    if (allmatch && flags.v) count = 0;
    OutputLCFlag(flags, numOfFiles, arrayOfFiles, count, i);
    fclose(file);
  }
  for (int i = 0; i < numOfPatterns; i++) {
    free(arrayOfPatterns[i]);
  }
}

void OutputLCFlag(Flags flags, int numOfFiles, char *arrayOfFiles[], int count,
                  int i) {
  if (flags.c && !flags.l)
    numOfFiles > 1 && !flags.h ? printf("%s:%d\n", arrayOfFiles[i], count)
                               : printf("%d\n", count);
  if (flags.l && count > 0 && flags.c) {
    if (numOfFiles > 1 && !flags.h)
      printf("%s:1\n%s\n", arrayOfFiles[i], arrayOfFiles[i]);
    else if (flags.h && numOfFiles > 1)
      printf("1\n%s\n", arrayOfFiles[i]);
    else if (numOfFiles < 2)
      printf("1\n%s\n", arrayOfFiles[i]);
  }
  if (count == 0 && flags.c && flags.l) {
    if (numOfFiles < 2 || (numOfFiles > 1 && flags.h)) printf("%d\n", count);
    if (!flags.h && numOfFiles > 1) printf("%s:%d\n", arrayOfFiles[i], count);
  }
  if (flags.l && !flags.c && count > 0) printf("%s\n", arrayOfFiles[i]);
}

void OutputNFlag(Flags flags, int numOfFiles, char *arrayOfFiles[], int i,
                 int numOfLines, char line[MAX_LINE_LENGTH],
                 int newlinePosition, int lineLength) {
  if (!flags.c && !flags.l) {
    if (flags.n) {
      if (numOfFiles > 1 && !flags.h)
        printf("%s:%d:%s", arrayOfFiles[i], numOfLines, line);
      if (numOfFiles < 2) printf("%d:%s", numOfLines, line);
      if (numOfFiles > 1 && flags.h) printf("%d:%s", numOfLines, line);
    } else {
      if (numOfFiles > 1 && !flags.h) printf("%s:%s", arrayOfFiles[i], line);
      if (numOfFiles < 2) printf("%s", line);
      if (numOfFiles > 1 && flags.h) printf("%s", line);
    }
    if (newlinePosition == lineLength) printf("\n");
  }
}