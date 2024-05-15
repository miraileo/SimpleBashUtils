TARGET = s21_grep
CC = gcc
FLAGS = -Werror -Wextra -Wall -std=c11

all: s21_grep

s21_grep:
	$(CC) $(FLAGS) -o $(TARGET) s21_grep.c parser.c s21_grep_funcs.c s21_grep.h

Google:
	clang-format -n -style=Google *.c *.h

clang:
	clang-format -n *.c *.h

clean:
	rm -f s21_grep