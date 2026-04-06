/*********************************************
 * Id: mill0999
 *
 * Selection Sort
 *********************************************/

#include <stdio.h>
#include <stdlib.h>

void printArray(int *A, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int n = argc - 1;

    int *A = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        A[i] = atoi(argv[i + 1]);
    }

    printArray(A, n);

    for (int i = 0; i < n - 1; i++) {
        int min = i;

        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[min]) {
                min = j;
            }
        }

        int tmp = A[i];
        A[i] = A[min];
        A[min] = tmp;

        printArray(A, n);
    }

    free(A);
    return 0;
}