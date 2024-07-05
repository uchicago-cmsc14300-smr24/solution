#include <stdlib.h>
#include <stdio.h>

int hex_char_to_int(char c);

void usage(const char *argv0, const char *msg);

int main(int argc, char *argv[])
{
    if (argc != 4) {
        usage("Wrong number of arguments", argv[0]);
    }

    int w = atoi(argv[1]);
    int h = atoi(argv[2]);

    if (w <= 0 || h <= 0) {
        usage("Invalid width or height", argv[0]);
    }

    char *color = argv[3];
    int rgb[3];

    for (int i = 0; i < 3; i += 1) {
        int idx = 2 + (i * 2);

        if (color[idx] == '\0' || color[idx + 1] == '\0') {
            usage("Not enough digits in color", argv[0]);
        }

        int d1 = hex_char_to_int(color[idx]);
        int d2 = hex_char_to_int(color[idx + 1]);

        if (d1 < 0 || d2 < 0) {
            usage("Invalid hex digit color", argv[0]);
        }

        rgb[i] = d1 * 16 + d2;
    }

    printf("P3\n");
    printf("%d %d\n255\n", w, h);

    for (int i = 0; i < w * h; i += 1) {
        float ratio = ((float) i / w) / h;
        int d1 = rgb[0] * ratio;
        int d2 = rgb[1] * ratio;
        int d3 = rgb[2] * ratio;
        printf("%d %d %d\n", d1, d2, d3);
    }

    return EXIT_SUCCESS;
}

void usage(const char *msg, const char *argv0)
{
    printf("%s\nusage: %s <width> <height> <hexcolor>\n", msg, argv0);
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
