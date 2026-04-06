#include <stdio.h>

// to run: ./a.out <test.ppm 

int main() {
    char line[256];
    
    while (scanf("%s", line) != EOF) {
        printf("%s\n", line);
    }
 
    return 0;
}