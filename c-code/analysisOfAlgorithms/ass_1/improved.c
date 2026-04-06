/*********************************************
 * Id: mill0999
 *
 * finds the min distance between to numbers,
 * but sorts first so min dist can be found in
 * one pass
 *********************************************/
#include <stdio.h>
#include <stdlib.h>

// minDist finds the min dist
int minDistSorted(int numArray[], int len);
// quicksort sorts an array using quicksort before we find min dist
void quicksort(int arr[], int low, int high);

// tis main
int main(int argc, char *argv[]) {
   int values[argc-1];

   for (int i = 0; i < argc-1; i++) {
      values[i] = atoi(argv[i+1]);
   }

   // quicksort with 0 as low and argc-2 as high
   quicksort(values, 0, (argc - 1) - 1);
   printf("%d\n", minDistSorted(values, argc-1));

   return 0;
}

// impl of minDist
int minDistSorted(int numArray[], int len) {
   int min = __INT_MAX__;
   int dist = 0;

   for (int i = 0; i < len-1; i++) {
      dist = numArray[i+1] - numArray[i];
      if (numArray[i+1] - numArray[i] < min) {
         min = dist;
      }
   }
   
   return min;
}

// Hoare partition scheme for the best quicksort performance
int partition(int arr[], int low, int high) {
   int pivot = arr[low + (high - low) / 2];
   int i = low - 1;
   int j = high + 1;

   while (1) {
      do {
         i++;
      } while (arr[i] < pivot);

      do {
         j--;
      } while (arr[j] > pivot);

      // When pointers cross or meet, partition is complete.
      if (i >= j) {
         return j;
      }

      int temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
   }
}

// recursive quicksort function
void quicksort(int arr[], int low, int high) {
   if (low >= high) {
      return;
   }

   int p = partition(arr, low, high);
   quicksort(arr, low, p);
   quicksort(arr, p + 1, high);
}
