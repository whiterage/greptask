#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    bool n;
    bool b;
    bool s;
    bool t;
    bool e;
} CatFlags;

CatFlags parse_flags(int *argc, char *argv[]) {
    CatFlags flags = {false, false, false, false, false};

    for (int i = 1; i < *argc;) {
        if (strcmp(argv[i], "-n") == 0) {
            flags.n = true;
        } else if (strcmp(argv[i], "-b") == 0) {
            flags.b = true;
        } else if (strcmp(argv[i], "-s") == 0) {
            flags.s = true;
        } else if (strcmp(argv[i], "-t") == 0) {
            flags.t = true;
        } else if (strcmp(argv[i], "-e") == 0) {
            flags.e = true;
        } else {
            i++;
            continue;
        }

        for (int j = i; j < *argc - 1; j++) {
            argv[j] = argv[j + 1];
        }
        (*argc)--;
    }

    if (flags.b) {
        flags.n = false;
    }

    return flags;
}

void flag_t_func(const char *line, CatFlags flags) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (flags.t && line[i] == '\t') {
            printf("^I");
        } else if (line[i] == '\n' && flags.e) {
            printf("$\n");
        } else {
            putchar(line[i]);
        }
    }
}

void cat_function(const char *filename, CatFlags flags) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Файл не найден: %s\n", filename);
        return;
    }

    char line[256];
    int line_number = 1;
    bool prev_empty = false;

    while (fgets(line, sizeof(line), file)) {
        if (flags.s && strcmp(line, "\n") == 0) {
            if (prev_empty) {
                continue;
            }
            prev_empty = true;
        } else {
            prev_empty = false;
        }

        if (flags.b && strcmp(line, "\n") != 0) {
            printf("%6d\t", line_number++);
        } else if (flags.n && !flags.b) {
            printf("%6d\t", line_number++);
        }

        if (flags.t || flags.e) {
            flag_t_func(line, flags);
        } else {
            printf("%s", line);
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("неверный формат ввода\n");
        return 1;
    }

    CatFlags flags = parse_flags(&argc, argv);

    for (int i = 1; i < argc; i++) {
        cat_function(argv[i], flags);
    }

    return 0;
}