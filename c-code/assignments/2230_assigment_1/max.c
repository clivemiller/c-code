#include "stdio.h"
#include "./arrayCalculator.h"

void Max(int array[]) {
    for (int i = 0; i < arrayLength; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }
}