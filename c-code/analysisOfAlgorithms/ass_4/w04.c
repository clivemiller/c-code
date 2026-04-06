/*********************************************
 * Id: mill0999
 *
 * behold: gaussian elimination in c
 *********************************************/
#include <stdio.h>
#include <stdlib.h>

// print the matrix with double loop
void printMatrix(int n, float A[n][n+1]);
// assemble the matrix from the values array
void assembleMatrix(int n, float A[n][n+1], float values[]);
// perform gaussian elimination
void GaussianElimination(int n, float A[n][n+1]);

// tis main
int main(int argc, char *argv[]) {
   // get n from command line
   int n = atoi(argv[1]);
   // init values array
   float values[argc-2];

   // create array of actual values
   for (int i = 0; i < argc - 2; i++) {
      values[i] = (float)atof(argv[i + 2]);
   }

   // create the matrix
   float Arr[n][n+1];

   // assemble the matrix
   assembleMatrix(n, Arr, values);
   // print the initial matrix
   printMatrix(n, Arr);
   // perform gaussian elimination
   GaussianElimination(n, Arr);

   return 0;
}

// impl of printMatrix
void printMatrix(int n, float A[n][n+1]) {
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n + 1; j++) {
         printf("%.2f ", A[i][j]);
      }
      printf("\n");
   }
   printf("\n");
}

// impl of assembleMatrix
void assembleMatrix(int n, float A[n][n+1], float values[]) {
   int indexer = 0;

   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n + 1; j++) {
         A[i][j] = values[indexer];
         indexer++;
      }
   }
}

// impl of GaussianElimination
void GaussianElimination(int n, float A[n][n+1]) {
   for (int i = 0; i < n - 1; i++) {
      for (int j = i + 1; j < n; j++) {
         float temp_ji = A[j][i];
         for (int k = i; k <= n; k++) {
            A[j][k] = A[j][k] - (A[i][k] * temp_ji / A[i][i]);
         }
      }

      printMatrix(n, A);
   }
}
