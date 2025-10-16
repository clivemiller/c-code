#include <stdio.h>

int main(int argc, char *argv[]) {
    int count = 0; // counter

    while (1) {
        FILE *file;
        file = fopen("./test.txt", "w");
        fprintf(file, "a");
        fclose(file);
    }

    return 0;
}
