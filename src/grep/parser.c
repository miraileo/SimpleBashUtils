#include "s21_grep.h"

void Parser(int argc, char *argv[], char *arrayOfFiles[],
            char *arrayOfPatterns[], int *numOfFiles, int *numOfPatterns,
            Flags *flags, int *allmatch) {
  int opt;
  char *filepathFFlag;
  while ((opt = getopt(argc, argv, "e:icvnoshlf:")) != -1) {
    switch (opt) {
      case 'i':
        flags->i = 1;
        break;
      case 'c':
        flags->c = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 'o':
        flags->o = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 'h':
        flags->h = 1;
        break;
      case 'e':
        flags->e = 1;
        arrayOfPatterns[*numOfPatterns] =
            calloc(strlen(optarg) + 1, sizeof(char));
        strcpy(arrayOfPatterns[*numOfPatterns], optarg);
        (*numOfPatterns)++;
        break;
      case 'f':
        flags->f = 1;
        filepathFFlag = optarg;
        FFlag(numOfPatterns, arrayOfPatterns, filepathFFlag, allmatch);
        break;
      case 'l':
        flags->l = 1;
        break;
    }
  }
  FileManager(*flags, argv, arrayOfPatterns, numOfPatterns, arrayOfFiles,
              numOfFiles, argc);
}

void FileManager(Flags flags, char *argv[], char *arrayOfPatterns[],
                 int *numOfPatterns, char *arrayOfFiles[], int *numOfFiles,
                 int argc) {
  FILE *fp = NULL;
  int patternISFound = 0;
  for (int i = optind; i < argc; i++) {
    if (!flags.e) {
      fp = fopen(argv[i], "r");
      if (fp == NULL && !patternISFound) {
        arrayOfPatterns[*numOfPatterns] =
            calloc(strlen(argv[i]) + 1, sizeof(char));
        strcpy(arrayOfPatterns[*numOfPatterns], argv[i]);
        (*numOfPatterns)++;
        patternISFound++;
      } else {
        arrayOfFiles[*numOfFiles] = argv[i];
        (*numOfFiles)++;
        fclose(fp);
      }
    } else {
      arrayOfFiles[*numOfFiles] = argv[i];
      (*numOfFiles)++;
    }
  }
}

void FFlag(int *numOfPatterns, char *arrayOfPatterns[], char *filepathFFlag,
           int *allmatch) {
  FILE *fp = NULL;
  int numLines = 0;
  char line[100];
  fp = fopen(filepathFFlag, "r");
  if (fp == NULL) {
    fprintf(stderr, "grep: %s: No such file or directory\n", filepathFFlag);
  } else {
    while (fgets(line, sizeof(line), fp)) {
      size_t lineLenght = strlen(line);
      if (line[lineLenght - 1] == '\n' && lineLenght != 1)
        line[lineLenght - 1] = '\0';
      if (line[0] == '\n') *allmatch = 1;
      arrayOfPatterns[*numOfPatterns] = calloc(strlen(line) + 1, sizeof(char));
      strcpy(arrayOfPatterns[*numOfPatterns], line);
      (*numOfPatterns)++;
      numLines++;
    }
    fclose(fp);
  }
}