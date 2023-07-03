#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct Options {
  int flag_b;
  int flag_e;
  int flag_n;
  int flag_s;
  int flag_t;
  int flag_v;
};

struct option Long_options[] = {{"number-nonblank", no_argument, 0, 'b'},
                                {"number", no_argument, 0, 'n'},
                                {"squeeze-blank", no_argument, 0, 's'},
                                {0, 0, 0, 0}};

struct Options options;

void scan_files(char *argv[], int cooked);
void cat(FILE *fp);
void cat_flags(FILE *fp);
void set_default(struct Options *options);