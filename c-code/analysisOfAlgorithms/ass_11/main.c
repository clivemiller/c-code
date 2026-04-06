/*********************************************
 * Id: mill0999
 *
 * insertion
 *********************************************/

#include <stdio.h>
#include <stdlib.h>

int n;

void printArray(int A[], int len, int pos) {
   for (int i = 0; i < len; i++) {
      if (i == pos) {
         printf("| %d ", A[i]);
      } else if (i < len-1) {
        printf("%d |", A[i]);
      } else {
         printf("%d ", A[i]);
      } 
   }
   printf("\n");
}

void insertionSort(int A[], int len, int pos) {
   printArray(A, len, pos);

   for (int i = 1; i<len; i++) {
      int v = A[i];
      int j = i-1;
      while (j >= 0 && A[j] > v) {
         A[j + 1] = A[j];
         j--;
      }
      A[j + 1] = v;

      printArray(A, len, pos);
   }
}

int main(int argc, char *argv[]) {
   n = argc - 1;

   int *A = malloc(n * sizeof(int));
   for (int i = 0; i < n; i++)
      A[i] = atoi(argv[i + 1]);

   insertionSort(A, n, 1);

   free(A);
   return 0;
}