#include <stdio.h>
#include <stdlib.h>

const int KEY = 15;

int is_upper_letter(char c)
{
    return 'A' <= c && c <= 'Z';
}

int is_lower_letter(char c)
{
    return 'a' <= c && c <= 'z';
}

int main(void)
{
    int c;
    while ((c = getchar()) != EOF) {
        char result;
        if (is_upper_letter(c)) {
            int n_alpha = c - 'A';
            if (n_alpha - KEY < 0) {
                n_alpha = n_alpha - KEY + 26;
            } else {
                n_alpha = n_alpha - KEY;
            }
            result = 'A' + n_alpha;
        } else if (is_lower_letter(c)) {
            int n_alpha = c - 'a';
            if (n_alpha - KEY < 0) {
                n_alpha = n_alpha - KEY + 26;
            } else {
                n_alpha = n_alpha - KEY;
            }
            result = 'a' + n_alpha;
        } else {
            result = c;
        }
        putchar(result);
    }

    return EXIT_SUCCESS;
}

