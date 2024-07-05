#include <stdio.h>
#include <stdlib.h>

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
    int counts[26] = { 0 };
    int total = 0;

    while ((c = getchar()) != EOF) {
        if (is_upper_letter(c)) {
            counts[c - 'A'] += 1;
            total += 1;
        } else if (is_lower_letter(c)) {
            counts[c - 'a'] += 1;
            total += 1;
        }
    }

    for (int i = 0; i < 26; i++) {
        double freq = (total != 0) ? (counts[i] / (double) total) : 0.0;
        printf("%c %6.2f\n", 'A' + i, freq * 100);
    }

    return EXIT_SUCCESS;
}

