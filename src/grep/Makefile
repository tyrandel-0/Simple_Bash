CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -g
OS=$(shell uname)

s21_grep:
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep

test:
	sh grep_test.sh

clean:
	rm -rf s21_grep s21_grep.dSYM *.o RESULT_VALGRIND.txt log.txt