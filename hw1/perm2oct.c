#include <stdlib.h>
#include <stdio.h>

int is_valid(int i, char c);
void usage(const char *argv0, const char *msg);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        usage("Wrong number of arguments", argv[0]);
    }

    char octs[3] = { 0 };

    for (int i = 0; i < 9; i++) {
        char c = argv[1][i];
        if (!is_valid(i, c)) {
            usage("Invalid permission string", argv[0]);
        }

        char bit = 4 >> (i % 3);
        if (c != '-') {
            octs[i / 3] |= bit;
        }
    }

    if (argv[1][9] != '\0') {
        usage("Invalid permission string", argv[0]);
    }

    printf("%d%d%d\n", octs[0], octs[1], octs[2]);

    return EXIT_SUCCESS;
}

int is_valid(int i, char c)
{
    if (c == '\0') {
        return 0;
    }

    if (c == '-') {
        return 1;
    }

    return (i % 3 == 0 && c == 'r')
        || (i % 3 == 1 && c == 'w')
        || (i % 3 == 2 && c == 'x');
}

void usage(const char *msg, const char *argv0)
{
    printf("%s\nusage: %s <perm-string>\n", msg, argv0);
    exit(EXIT_FAILURE);
}
