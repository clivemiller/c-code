#include "stdio.h"
#include "./arrayCalculator.h"

void Min(int array[]) {
    for (int i = 0; i < arrayLength; i++)
    {
        if (array[i] < min)
        {
            min = array[i];
        }
    }
}