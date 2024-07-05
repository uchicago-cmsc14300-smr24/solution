#include <stdlib.h>
#include <stdio.h>

int hex_char_to_int(char c);

void usage(const char *argv0, const char *msg);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        usage("Wrong number of arguments", argv[0]);
    }

    char *input = argv[1];

    if (input[0] != '0' || input[1] != 'x') {
        usage("Hex number should start with 0x", argv[0]);
    }

    int rgb[3];

    for (int i = 0; i < 3; i += 1) {
        int idx = 2 + (i * 2);

        if (input[idx] == '\0' || input[idx + 1] == '\0') {
            usage("Not enough digits in color", argv[0]);
        }

        int d1 = hex_char_to_int(input[idx]);
        int d2 = hex_char_to_int(input[idx + 1]);

        if (d1 < 0 || d2 < 0) {
            usage("Invalid hex digit color", argv[0]);
        }

        rgb[i] = d1 * 16 + d2;
    }

    if (input[8] != '\0') {
        usage("Color has too many digits", argv[0]);
    }

    printf("%d %d %d\n", rgb[0], rgb[1], rgb[2]);

    return EXIT_SUCCESS;
}

void usage(const char *msg, const char *argv0)
{
    printf("%s\nusage: %s <hexcolor>\n", msg, argv0);
    exit(EXIT_FAILURE);
}

int hex_char_to_int(char c)
{
    if ('0' <= c && c <= '9') {
        return c - '0';
    }

    if ('A' <= c && c <= 'F') {
        return 10 + c - 'A';
    }

    return -1;
}
