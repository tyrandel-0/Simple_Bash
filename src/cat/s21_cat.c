#include "s21_cat.h"

int main(int argc, char *argv[]) {
  set_default(&options);

  char ch;
  int long_index = 0;

  while ((ch = getopt_long(argc, argv, "benstuvET", Long_options,
                           &long_index)) != -1) {
    switch (ch) {
      case 'b':
        options.flag_b = options.flag_n = 1;
        break;
      case 'e':
        options.flag_e = options.flag_v = 1;
        break;
      case 'n':
        options.flag_n = 1;
        break;
      case 's':
        options.flag_s = 1;
        break;
      case 't':
        options.flag_t = options.flag_v = 1;
        break;
      case 'v':
        options.flag_v = 1;
        break;
      case 'E':
        options.flag_e = 1;
        break;
      case 'T':
        options.flag_t = 1;
        break;
      default:
        fprintf(stderr, "usage: ./s21_cat [-benstuv] [file ...]\n");
        exit(1);
    }
  }

  argv += optind;

  if (options.flag_b || options.flag_e || options.flag_n || options.flag_s ||
      options.flag_t || options.flag_v)
    scan_files(argv, 1);
  else
    scan_files(argv, 0);
}

void set_default(struct Options *options) {
  options->flag_b = 0;
  options->flag_e = 0;
  options->flag_n = 0;
  options->flag_s = 0;
  options->flag_t = 0;
  options->flag_v = 0;
}

void scan_files(char *argv[], int flag_s_detected) {
  int i = 0;
  char *path;
  FILE *fp;

  while ((path = argv[i]) != NULL || i == 0) {
    if (path == NULL || strcmp(path, "-") == 0)
      fp = stdin;
    else
      fp = fopen(path, "r");
    if (fp == NULL)
      fprintf(stderr, "./s21_cat: %s: No such file or directory\n", path);
    else {
      if (flag_s_detected)
        cat_flags(fp);
      else
        cat(fp);

      if (fp != stdin) fclose(fp);
    }

    if (path == NULL) break;
    i++;
  }
}

void cat(FILE *fp) {
  char ch;
  while ((ch = fgetc(fp)) != EOF) {
    putchar(ch);
  }
}

void cat_flags(FILE *fp) {
  int ch;
  int skip_empty_lines = 0;
  int line_num = 1;
  for (int prev = '\n'; (ch = fgetc(fp)) != EOF; prev = ch) {
    if (prev == '\n') {
      if (options.flag_s) {
        if (ch == '\n' && skip_empty_lines) continue;
        skip_empty_lines = (ch == '\n');
      }
      if (options.flag_n && (!options.flag_b || ch != '\n')) {
        printf("%6d\t", line_num);
        line_num++;
      }
    }
    if (ch == '\n') {
      if (options.flag_e) printf("$");
    } else if (ch == '\t') {
      if (options.flag_t) {
        printf("^I");
        continue;
      }
    } else if (options.flag_v) {
      if (ch >= 0 && ch <= 31 && ch != 10 && ch != 9) {
        printf("^%c", ch + 64);
        continue;
      }
      if (ch == 127) {
        printf("^?");
        continue;
      }
    }

    printf("%c", ch);
  }
}
