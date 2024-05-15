#include <getopt.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
  int t;
  int e;
  int b;
  int n;
  int s;
  int v;
  int E;
  int T;
} Flags;

void Parser(int argc, char *argv[], Flags *flags);

void Cat(Flags flags, int argc, char *argv[]);