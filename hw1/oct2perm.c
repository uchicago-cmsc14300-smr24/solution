#include <stdlib.h>
#include <stdio.h>

void usage(const char *argv0, const char *msg);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        usage("Wrong number of arguments", argv[0]);
    }

    char perm[10] = "---------";

    for (int i = 0; i < 3; i++) {
        char c = argv[1][i];

        if (c == '\0') {
            usage("Not enough digits", argv[0]);
        }
        int digit = c - '0';
        if (digit < 0 || digit > 7) {
            usage("Not within [0-7]", argv[0]);
        }

        int idx = i * 3;

        if (digit & 4) {
            perm[idx] = 'r';
        }
        if (digit & 2) {
            perm[idx + 1] = 'w';
        }
        if (digit & 1) {
            perm[idx + 2] = 'x';
        }
    }

    if (argv[1][3] != '\0') {
        usage("Too many digits", argv[0]);
    }

    printf("%s\n", perm);

    return EXIT_SUCCESS;
}

void usage(const char *msg, const char *argv0)
{
    printf("%s\nusage: %s nnn\n", msg, argv0);
    exit(EXIT_FAILURE);
}
