TARGET = s21_cat
CC = gcc
FLAGS = -Wextra -Werror -Wall -std=c11

all: s21_cat

s21_cat:
	$(CC) $(FLAGS) -o $(TARGET) s21_cat.c s21_cat_funcs.c s21_cat.h parser.c

Google:
	clang-format -n -style=Google *.c *.h

clang:
	clang-format -n *.c *.h

clean:
	rm -f s21_cat