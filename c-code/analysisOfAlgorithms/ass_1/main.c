/*********************************************
 * Id: mill0999
 *
 * finds the min distance between to numbers
 *********************************************/
#include <stdio.h>
#include <stdlib.h>

// minDist finds the min dist
int minDist(int numArray[], int len);

// tis main
int main(int argc, char *argv[]) {
   int values[argc-1];

   for (int i = 0; i < argc-1; i++) {
      values[i] = atoi(argv[i+1]);
   }
   printf("%d\n", minDist(values, argc-1));

   return 0;
}

// impl of minDist
int minDist(int numArray[], int len) {
   int min = __INT_MAX__;

   for (int i = 0; i < len-1; i++) {
      for (int j = i+1; j < len; j++) {
         if(abs(numArray[i] - numArray[j]) < min) {
            min = abs(numArray[i] - numArray[j]);
         }
      }
   }
   
   return min;
}
