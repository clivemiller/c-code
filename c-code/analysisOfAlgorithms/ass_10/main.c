/*********************************************
 * Id: mill0999
 *
 * HoarePartition
 *********************************************/

#include <stdio.h>
#include <stdlib.h>

int n;

void swap(int *A, int i, int j) {
   int tmp = A[i];
   A[i] = A[j];
   A[j] = tmp;
}

void printSubArray(int *A, int l, int r) {
   for (int k = 0; k < n; k++) {
      if (k == l) {
         printf("[");
      }

      printf("%d", A[k]);
      if (k == r) {
         printf("]");
         if (k < n - 1) {
            printf(" "); // extra space after closing bracket
         }
      }

      if (k < n - 1) {
         printf(" ");
      }
   }

   printf("\n");
}

int hoarePartition(int *A, int l, int r) {
   int p = A[l];
   int i = l;
   int j = r + 1;

   while (1) {
      do {
         i++;
      } while (i <= r && A[i] < p);

      do {
         j--;
      } while (A[j] > p);

      if (i >= j) {
         break;
      }

      swap(A, i, j);
   }

   swap(A, l, j);
   return j;
}

void quicksort(int *A, int l, int r) {
   if (l < r) {
      int s = hoarePartition(A, l, r);
      quicksort(A, l, s - 1);
      quicksort(A, s + 1, r);
      printSubArray(A, l, r);
   }
}

int main(int argc, char *argv[]) {
   n = argc - 1;

   int *A = malloc(n * sizeof(int));
   for (int i = 0; i < n; i++)
      A[i] = atoi(argv[i + 1]);

   quicksort(A, 0, n - 1);

   free(A);
   return 0;
}