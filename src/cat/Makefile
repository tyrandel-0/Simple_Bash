CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -g
OS=$(shell uname)

s21_cat:
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat

test:
	sh cat_test.sh

clean:
	rm -rf s21_cat s21_cat.dSYM *.o RESULT_VALGRIND.txt log.txt