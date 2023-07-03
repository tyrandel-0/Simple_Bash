#include "s21_grep.h"

int main(int argc, char *argv[]) {
  set_default(&options);
  char flag;
  while ((flag = getopt_long(argc, argv, "e:ivclnhs", NULL, 0)) != -1) {
    switch (flag) {
      case 'e':
        options.flag_e = 1;
        add_template(optarg);
        break;
      case 'i':
        options.flag_i = 1;
        break;
      case 'v':
        options.flag_v = 1;
        break;
      case 'c':
        options.flag_c = 1;
        break;
      case 'l':
        options.flag_l = 1;
        break;
      case 'n':
        options.flag_n = 1;
        break;
      case 'h':
        options.flag_h = 1;
        break;
      case 's':
        options.flag_s = 1;
        break;
      default:
        fprintf(
            stderr,
            "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "
            "[-C[num]]\n\t[-e pattern] [-f file] [--binary-files=value] "
            "[--color=when]\n\t[--context[=num]] [--directories=action] "
            "[--label] [--line-buffered]\n\t[--null] [pattern] [file ...]\n");
        return 1;
    }
  }

  if (!options.flag_e) add_template(argv[optind]);
  scan_files(argv, argc);
}

void scan_files(char *argv[], int argc) {
  int i = (options.flag_e) ? optind : optind + 1;
  int num_of_files = argc - i;
  FILE *fp;
  for (; i < argc; i++) {
    fp = fopen(argv[i], "r");
    if (fp == NULL) {
      if (!options.flag_s)
        fprintf(stderr, "%s: No such file or directory\n", argv[i]);
    } else {
      for (int j = 0; options.templates[j] != NULL; j++) {
        grep(fp, options.templates[j], num_of_files, argv[i]);
      }
      fclose(fp);
    }
  }
}

void grep(FILE *fp, char *template, int num_of_files, char *filename) {
  int line_size = 1024;
  int count_of_matches = 0;
  int line_num = 1;
  char line[line_size];
  regex_t regex;
  int i_case = options.flag_i ? REG_ICASE : REG_EXTENDED;
  int result = regcomp(&regex, template, i_case);

  if (result != 0) {
    fprintf(stderr, "parsing regex error\n");
    regfree(&regex);
    return;
  }

  while (fgets(line, line_size, fp) != NULL) {
    int isRegex = regexec(&regex, line, 0, NULL, 0) == 0;
    if ((isRegex && !options.flag_v) || (!isRegex && options.flag_v)) {
      if (!options.flag_c) {
        if (options.flag_l) {
          printf("%s\n", filename);
          break;
        } else {
          if (num_of_files > 1 && !options.flag_h) {
            printf("%s:", filename);
          }
          if (options.flag_n) {
            printf("%d:", line_num);
          }
          printf("%s", line);
          if (strchr(line, '\n') == NULL) {
            printf("\n");
          }
        }
      }
      count_of_matches++;
    }
    line_num++;
  }

  if (options.flag_c) {
    if (num_of_files > 1 && !options.flag_h) printf("%s:", filename);
    printf("%d\n", count_of_matches);
  }

  regfree(&regex);
}

void add_template(char *elem) {
  options.templates[options.templates_count] = elem;
  options.templates_count++;
}

void set_default(struct Options *options) {
  options->flag_e = 0;
  options->flag_i = 0;
  options->flag_v = 0;
  options->flag_c = 0;
  options->flag_l = 0;
  options->flag_n = 0;
  options->flag_h = 0;
  options->flag_s = 0;
  options->templates_count = 0;
}