CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror

CAT_SRC = src/s21_cat.c
CAT_BIN = s21_cat

all: s21_cat

s21_cat: $(CAT_SRC)
	$(CC) $(CFLAGS) -o $(CAT_BIN) $(CAT_SRC)

clean:
	rm -f $(CAT_BIN)

rebuild: clean all