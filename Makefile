CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror

CAT_SRC = src/s21_cat.c
CAT_BIN = s21_cat
GREP_SRC	=	src/s21_grep.c
GREP_BIN	=	s21_grep

all: s21_cat s21_grep

s21_cat: $(CAT_SRC)
	$(CC) $(CFLAGS) -o $(CAT_BIN) $(CAT_SRC)

s21_grep:	$(GREP_SRC)
	$(CC) $(CFLAGS) -o $(GREP_BIN) $(GREP_SRC)

clean:
	rm -f $(CAT_BIN) $(GREP_BIN)

rebuild: clean all