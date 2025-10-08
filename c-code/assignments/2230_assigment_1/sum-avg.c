#include "stdio.h"
#include "./arrayCalculator.h"

void SumAndAvg(int array[]) {
    for (int i = 0; i < arrayLength; i++)
    {
        sum += array[i];
    }

    average = sum/arrayLength;
}