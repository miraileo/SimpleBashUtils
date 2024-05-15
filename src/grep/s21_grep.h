#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATTERNS 40
#define MAX_FILES 30
#define MAX_LINE_LENGTH 2048

typedef struct {
  int c;
  int n;
  int i;
  int v;
  int l;
  int e;
  int h;
  int o;
  int s;
  int f;
} Flags;

void Grep(char *arrayOfFiles[], char *arrayOfPatterns[], int numOfFiles,
          int numOfPatterns, Flags flags, int allmatch);

void Parser(int argc, char *argv[], char *arrayOfFiles[],
            char *arrayOfPatterns[], int *numOfFiles, int *numOfPatterns,
            Flags *flags, int *allmatch);

int StrStr(char *line, char *pattern, Flags flags);

int EndLineFinder(char *pattern);

int CompareLastWordWithPattern(char *line, char *pattern);

void FileManager(Flags flags, char *argv[], char *arrayOfPatterns[],
                 int *numOfPatterns, char *arrayOfFiles[], int *numOfFiles,
                 int argc);

void OutputLCFlag(Flags flags, int numOfFiles, char *arrayOfFiles[], int count,
                  int i);

void OutputNFlag(Flags flags, int numOfFiles, char *arrayOfFiles[], int i,
                 int numOfLines, char line[MAX_LINE_LENGTH],
                 int newlinePosition, int lineLength);

void FFlag(int *numOfPatterns, char *arrayOfPatterns[], char *filepathFFlag,
           int *allmatch);