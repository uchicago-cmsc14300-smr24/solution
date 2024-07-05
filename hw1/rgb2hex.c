#include <stdio.h>
#include <stdlib.h>

int to_i(char *str);

void usage(const char *argv0, const char *msg);

char to_hex_digit(int i);

int main(int argc, char *argv[])
{
    if (argc != 4) {
        usage("Wrong number of arguments", argv[0]);
    }

    char hex[9] = { '0', 'x', 0, 0, 0, 0, 0, 0, 0 };

    for (int i = 0; i < 3; i += 1) {
        int number = to_i(argv[i + 1]);
        if (number < 0 || number > 255) {
            usage("Color value is not an integer within [0, 255]", argv[0]);
        }
        int idx = 2 + i * 2;
        hex[idx] = to_hex_digit(number / 16);
        hex[idx + 1] = to_hex_digit(number % 16);
    }

    printf("%s\n", hex);

    return EXIT_SUCCESS;
}

int to_i(char *str)
{
    int result = 0;
    for (int i = 0; ; i += 1) {
        char c = str[i];
        if (c == '\0') {
            break;
        }
        if (c < '0' || c > '9') {
            return -1;
        }
        result = result * 10 + (str[i] - '0');
    }

    return result;
}

void usage(const char *msg, const char *argv0)
{
    printf("%s\nusage: %s <r-color> <g-color> <b-color>\n", msg, argv0);
    exit(EXIT_FAILURE);
}

char to_hex_digit(int i)
{
    if (0 <= i && i < 10) {
        return '0' + i;
    }

    if (10 <= i && i < 16) {
        return 'A' + i - 10;
    }

    return '?';
}

