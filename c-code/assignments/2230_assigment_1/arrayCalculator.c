#include "stdio.h"
#include <limits.h>
#include "./arrayCalculator.h"

// Define the global variables here (only in one file!)
int array[] = {-10, 30, 33, -154, 2, 150, 20, 53, 90, 1, -30, 7, 193, 25};
int arrayLength = 14;
int max = INT_MIN;
int min = INT_MAX;
int sum = 0;
int average = 0;

void main ()
{
    Min(array);
    Max(array);
    SumAndAvg(array);

    printf("The min is: %d\n", min);
    printf("The max is: %d\n", max);
    printf("The sum is: %d\n", sum);
    printf("The average is: %d\n", average);
}