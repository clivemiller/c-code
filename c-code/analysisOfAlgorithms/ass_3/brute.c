/*********************************************
 * Id: mill0999
 *
 * brute force impl of formula 2^n = 2^(n−1) + 2^(n−1)
 *********************************************/
#include <stdio.h>
#include <stdlib.h>

//  finds 2^n recursively
int recursiveFormula(int n);

// tis main
int main(int argc, char *argv[]) {
   int n = atoi(argv[1]);

   printf("2^%d: %d\n", n, recursiveFormula(n));

   return 0;
}

// impl of recursiveFormula
int recursiveFormula(int n) {
   if (n<1) {
      return 1;
   }
   
   return recursiveFormula(n-1) + recursiveFormula(n-1);
}
