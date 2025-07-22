#ifndef S21_GREP_H
#define S21_GREP_H

#include <stdbool.h>

typedef struct {
    bool i, v, c;
} GrepFlags;

GrepFlags parse_flags(int *argc, char *argv[]);
void grep_func(const char *pattern, const char *filename, GrepFlags flags);

#endif

