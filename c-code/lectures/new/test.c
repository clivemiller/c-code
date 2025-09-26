#include <stdio.h>

void main() 
{
    int p = -5;

    if (p < sizeof(int))
    {
        printf("True");
    }
    else 
    {
        printf("False");
    }
}