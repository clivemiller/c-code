#include <stdio.h>

int main( int num_of_args, char *array_of_args[]) 
{
    for ( int i = 1; i < num_of_args; i++)
    {
        printf("| %s |\n", array_of_args[i]);
    }
}