#include <stdio.h>
#include <stdlib.h>

void main() {
    FILE * read_pointer = fopen( "./readFrom/reader.txt", "r");
    
    int c;
    while ((c = fgetc(read_pointer)) != EOF) {
       putchar(c);
    }

    fclose(read_pointer);
}
    