#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool check_flag_e(int *argc, char *argv[]) {
    for (int i = 1; i < *argc; i++) {
        if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "-b") == 0 ||
            strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "-t") == 0) {
            continue;
        }

        if (strcmp(argv[i], "-e") == 0) {
            for (int j = i; j < *argc - 1; j++) {
                argv[j] = argv[j + 1];
            }
            (*argc)--;
            return true;
        }
    }
    return false;
}

bool check_flag_t(int *argc, char *argv[]) {
    for (int i = 1; i < *argc; i++) {
        if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "-b") == 0 ||
            strcmp(argv[i], "-s") == 0) {
            continue;
        }

        if (strcmp(argv[i], "-t") == 0) {
            for (int j = i; j < *argc - 1; j++) {
                argv[j] = argv[j + 1];
            }
            (*argc)--;
            return true;
        }
    }

    return false;
}

bool check_flag_s(int *argc, char *argv[]) {
    for (int i = 1; i < *argc; i++) {
        if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "-b") == 0) {
            continue;
        }

        if (strcmp(argv[i], "-s") == 0) {
            for (int j = i; j < *argc - 1; j++) {
                argv[j] = argv[j + 1];
            }
            (*argc)--;
            return true;
        }
    }

    return false;
}

bool check_flag_b(int *argc, char *argv[]) {
    for (int i = 1; i < *argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            continue;
        }

        if (strcmp(argv[i], "-b") == 0) {
            for (int j = i; j < *argc - 1; j++) {
                argv[j] = argv[j + 1];
            }
            (*argc)--;
            return true;
        }
    }
    return false;
}

bool check_flag_n(int *argc, char *argv[]) {
    for (int i = 1; i < *argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            for (int j = i; j < *argc - 1; j++) {
                argv[j] = argv[j + 1];
            }
            (*argc)--;
            return true;
        }
    }
    return false;
}

void flag_t_func(const char *line, bool flag_e) {
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '\t') {
            printf("^I");
        } else if (line[i] == '\n' && flag_e) {
            printf("$\n");
        } else {
            putchar(line[i]);
        }
    }
}

void cat_function(const char *filename, bool flag_n, bool flag_b, bool flag_s, bool flag_t,
                  bool flag_e) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Файл не найден: %s\n", filename);
        return;
    }

    char line[256];
    int line_number = 1;
    bool prev_empty = false;

    while (fgets(line, sizeof(line), file)) {
        if (flag_s && strcmp(line, "\n") == 0) {
            if (prev_empty) {
                continue;
            }
            prev_empty = true;
        } else {
            prev_empty = false;
        }

        if (flag_b && strcmp(line, "\n") != 0) {
            printf("%6d\t", line_number++);
        } else if (flag_n && !flag_b) {
            printf("%6d\t", line_number++);
        }

        if (flag_t || flag_e) {
            flag_t_func(line, flag_e);
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

    bool flag_n = check_flag_n(&argc, argv);
    bool flag_b = check_flag_b(&argc, argv);
    bool flag_s = check_flag_s(&argc, argv);
    bool flag_t = check_flag_t(&argc, argv);
    bool flag_e = check_flag_e(&argc, argv);

    if (flag_b) {
        flag_n = false;
    }

    for (int i = 1; i < argc; i++) {
        cat_function(argv[i], flag_n, flag_b, flag_s, flag_t, flag_e);
    }

    return 0;
}