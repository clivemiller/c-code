#include <stdio.h>

// to run: ./a.out <test.ppm 

int main() {
    char fmt[3];
    int v,h;
 
    scanf("%s", fmt);
    scanf("%d %d", &v, &h);
 
    printf("%s\n", fmt);
    printf("%d %d\n", v, h);
 
    return 0;
}