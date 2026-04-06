#include <stdio.h>
#include <stdlib.h>

void printMatrix(double **matrix, int rows, int cols) {
   for (int i = 0; i < rows; i++) {
       for (int j = 0; j < cols; j++) {
           printf("%8.3f ", matrix[i][j]);
       }
       printf("\n");
   }
}

int main() {
   printf("Echelon Solver Initialized.\n");
   printf("Enter the amount of unknowns: ");
   int unknowns;
   scanf("%d", &unknowns);
   printf("Enter the number of equations: ");
   int equations;
   scanf("%d", &equations);

   // Allocate memory for the augmented matrix
   double **matrix = (double **)malloc(equations * sizeof(double *));
   for (int i = 0; i < equations; i++) {
       matrix[i] = (double *)malloc((unknowns + 1) * sizeof(double));
   }

   printf("Enter the augmented matrix coefficients row by row:\n");
   for (int i = 0; i < equations; i++) {
       for (int j = 0; j < unknowns + 1; j++) {
           scanf("%lf", &matrix[i][j]);
       }
   }

   printMatrix(matrix, unknowns, equations);



   return 0;
}