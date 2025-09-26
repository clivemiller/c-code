#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "header.h"

// to compile : cc svu.c main.c

int main( int argc, char * argv[] )
{
    if (argc < 4) {
        fprintf(stderr, "usage: %s L W n\n", argv[0]);
        return 1;
    }

    double L = atof(argv[1]);
    double W = atof(argv[2]);
    int n = atoi(argv[3]);

    Set(W, L, n);

    Calculate();

    PrintMeasurements();
  
    return 0;
}
