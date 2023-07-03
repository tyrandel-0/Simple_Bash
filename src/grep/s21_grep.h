#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Options {
  int flag_e;
  int flag_i;
  int flag_v;
  int flag_c;
  int flag_l;
  int flag_n;
  int flag_s;
  int flag_h;
  char *templates[1000];
  int templates_count;
};

struct Options options;

void scan_files(char *argv[], int argc);
void set_default(struct Options *options);
void grep(FILE *fp, char *template, int num_of_files, char *filename);
void add_template(char *elem);