#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

typedef struct {
    bool i, v, c, l, n, h, s, o;
} GrepFlags;

GrepFlags parse_flags(int *argc, char *argv[]) {
    GrepFlags flags = {false};

    for (int i = 1; i < *argc;) {
        if (argv[i][0] == '-' && argv[i][1] != '\0') {
            for (int j = 1; argv[i][j] != '\0'; j++) {
                switch (argv[i][j]) {
                    case 'i':
                        flags.i = true;
                        break;
                    case 'v':
                        flags.v = true;
                        break;
                    case 'c':
                        flags.c = true;
                        break;
                    case 'l':
                        flags.l = true;
                        break;
                    case 'n':
                        flags.n = true;
                        break;
                    case 'h':
                        flags.h = true;
                        break;
                    case 's':
                        flags.s = true;
                        break;
                    case 'o':
                        flags.o = true;
                        break;
                    default:
                        fprintf(stderr, "Unknown flag: -%c\n", argv[i][j]);
                        break;
                }
            }

            for (int k = i; k < *argc - 1; k++) {
                argv[k] = argv[k + 1];
            }
            (*argc)--;
        } else {
            i++;
        }
    }

    return flags;
}

void grep_func(const char *pattern, const char *filename, GrepFlags flags, bool mult_files) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        if (!flags.s) {
            printf("Файл %s не найден\n", filename);
        }
        return;
    }

    char line[256];
    int count = 0;
    int line_number = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;
        char *found = flags.i ? strcasestr(line, pattern) : strstr(line, pattern);

        if ((flags.o && found)) {
            char *start = line;
            while ((start = (flags.i ? strcasestr(start, pattern) : strstr(start, pattern))) !=
                   NULL) {
                printf("%.*s\n", (int)strlen(pattern), start);
                start += strlen(pattern);
            }
            continue;
        }

        if ((flags.v && !found) || (!flags.v && found)) {
            count++;

            if (flags.l) {
                printf("%s\n", filename);
                break;
            }

            if (!flags.c) {
                if (!flags.h && mult_files) {
                    printf("%s:%s", filename, line);
                }
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

    const char *pattern = argv[1];

    int file_start = 2;
    int file_count = argc - file_start;
    bool mult_files = file_count > 1;

    for (int i = file_start; i < argc; i++) {
        grep_func(pattern, argv[i], flags, mult_files);
    }

    return 0;
}