#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int needspace = 0;
    for (int i = 1; i < argc; i += 1) {
        if (needspace) {
            putchar(' ');
        }
        printf("%s", argv[i]);
        needspace = 1;
    }
    putchar('\n');

    return EXIT_SUCCESS;
}
