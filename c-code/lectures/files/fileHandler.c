#include <stdio.h>

int main(int argc, char **argv) {
    FILE *f = fopen(argv[1], "r");
    int c;

    while ((c = fgetc(f)) != EOF)
        putchar(c);

    fclose(f);  
    return 0;
}
