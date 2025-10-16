#include <stdio.h>

int main(int argc, char *argv[]) {
    int count = 0; // counter

    while (1) {
        int num = (100 + 20 / 23)*12;
        fprintf(stderr, "Calc ans is: %d \n", num);
    }

    return 0;
}
