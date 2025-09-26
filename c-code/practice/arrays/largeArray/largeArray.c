#include <stdio.h>

int main(void) 
{
    int array[50000] = {1, 2, 3, 4};

    printf(" size of array: %ld\n", sizeof(array));
    printf(" array[2]: %d\n", array[2]);
    printf(" array[10]: %d\n", array[10]);
}