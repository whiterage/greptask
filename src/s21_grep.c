#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

typedef struct {
    bool i, v, c, l, n;
} GrepFlags;

GrepFlags parse_flags(int *argc, char *argv[]) {
    GrepFlags flags = {false, false, false, false, false};

    for (int i = 1; i < *argc;) {
        if (strcmp(argv[i], "-i") == 0) {
            flags.i = true;
        } else if (strcmp(argv[i], "-v") == 0) {
            flags.v = true;
        } else if (strcmp(argv[i], "-c") == 0) {
            flags.c = true;
        } else if (strcmp(argv[i], "-l") == 0) {
            flags.l = true;
        } else if (strcmp(argv[i], "-n") == 0) {
            flags.n = true;
        } else {
            i++;
            continue;
        }

        for (int j = i; j < *argc - 1; j++) {
            argv[j] = argv[j + 1];
        }
        (*argc)--;
    }

    return flags;
}

void grep_func(const char *pattern, const char *filename, GrepFlags flags) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Файл %s не найден\n", filename);
        return;
    }

    char line[256];
    int count = 0;
    int line_number = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        char *found = flags.i ? strcasestr(line, pattern) : strstr(line, pattern);

        if ((flags.v && !found) || (!flags.v && found)) {
            count++;

            if (flags.l) {
                printf("%s\n", filename);
                break;
            }

            if (!flags.c) {
                if (flags.n) {
                    printf("%d:", line_number);
                }
                printf("%s", line);
            }
        }
    }

    if (flags.c) {
        printf("%d\n", count);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s [options] pattern filename\n", argv[0]);
        return 1;
    }

    GrepFlags flags = parse_flags(&argc, argv);
    const char *pattern = argv[argc - 2];
    const char *filename = argv[argc - 1];

    grep_func(pattern, filename, flags);
    return 0;
}