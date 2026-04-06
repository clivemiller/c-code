/*********************************************
 * Id: mill0999
 *
 * behold: kind of a modified ternary tower of hanoi in c, but not restrictive
 *********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// init_A_array initializes the A array with disk numbers
void init_A_array(int n, int Arr[]);
// init_Zero_array initializes an array with zeros
void init_Zero_array(int n, int Arr[]);
// printMoveDisk prints the move
void printMoveDisk(char from_rod, char to_rod);
// ternaryHanoiDisk performs the Tower of Hanoi algorithm
void ternaryHanoiDisk(int n, int A[n], int B[n], int C[n]);
// moveXtoY moves the top disk from array X to array Y
void moveXtoY(int n, int X[n], int Y[n]);


// tis main
int main(int argc, char *argv[]) {
   if (argc < 2) return 1; 
   int disk_count = atoi(argv[1]);

   int A[disk_count];
   int B[disk_count];
   int C[disk_count];

   init_A_array(disk_count, A);
   init_Zero_array(disk_count, B);
   init_Zero_array(disk_count, C);

   ternaryHanoiDisk(disk_count, A, B, C);

   return 0;
}

// impl of init_A_array
void init_A_array(int n, int Arr[]) {
   for (int i = 0; i < n; i++) {
      Arr[i] = i+1;
   }
}

// impl of init_Zero_array
void init_Zero_array(int n, int Arr[]) {
   for (int i = 0; i < n; i++) {
      Arr[i] = 0;
   }
}

// impl of printMoveDisk
void printMoveDisk(char from_rod, char to_rod) {
   printf("Move %c TO %c\n", from_rod, to_rod);
}

// impl of ternaryHanoiDisk
void ternaryHanoiDisk(int n, int A[n], int B[n], int C[n]) {
   // direction depends on if n is even or odd
   int smallest_direction = (n % 2 == 0) ? 1 : 2; 
   int smallest_peg = 0; // 0=A,1=B,2=C

   for (int i = 1; i < pow(2, n); i++) {
      int least_significate_bit = i & 1;

      if (least_significate_bit == 1) {
         int next_peg = (smallest_peg + smallest_direction) % 3;
         char from_name = (smallest_peg == 0) ? 'A' : (smallest_peg == 1) ? 'B' : 'C';
         char to_name = (next_peg == 0) ? 'A' : (next_peg == 1) ? 'B' : 'C';
         
         int* from_arr = (smallest_peg == 0) ? A : (smallest_peg == 1) ? B : C;
         int* to_arr = (next_peg == 0) ? A : (next_peg == 1) ? B : C;

         moveXtoY(n, from_arr, to_arr);
         printMoveDisk(from_name, to_name);
         smallest_peg = next_peg;
      } else {
         // Move the only legal non-smallest disk
         int peg1 = (smallest_peg + 1) % 3;
         int peg2 = (smallest_peg + 2) % 3;

         // Determine which array (A, B, or C) is pegs
         // If peg is 0, use A; if 1, use B; otherwise use C
         int* arr1 = (peg1 == 0) ? A : (peg1 == 1) ? B : C;
         int* arr2 = (peg2 == 0) ? A : (peg2 == 1) ? B : C;

         // use peg to get move names
         // 0 -> 'A', 1 -> 'B', 2 -> 'C'
         char name1 = (peg1 == 0) ? 'A' : (peg1 == 1) ? 'B' : 'C';
         char name2 = (peg2 == 0) ? 'A' : (peg2 == 1) ? 'B' : 'C';
         
         // tops are so we dont execute an unneeded operation
         int top1 = 0, top2 = 0;
         for (int j = 0; j < n; j++) {
            if (arr1[j] != 0) { top1 = arr1[j];
               break;
            }
         }

         for (int j = 0; j < n; j++) {
            if (arr2[j] != 0) {
               top2 = arr2[j];
               break;
            }
         }
         
         // check if the move makes sense to make
         if (top1 != 0 && (top2 == 0 || top1 < top2)) {
            moveXtoY(n, arr1, arr2);
            printMoveDisk(name1, name2);
         } else {
            moveXtoY(n, arr2, arr1);
            printMoveDisk(name2, name1);
         }
      }
   }
}

// impl of moveXtoY
void moveXtoY(int n, int X[n], int Y[n]) {
   int diskToMove = 0;
   for (int i = 0; i < n; i++) {
      if (X[i] != 0) {
         diskToMove = X[i];
         X[i] = 0;
         break;
      }
   }

   // Find the first empty slot from the bottom up to avoid i-1 index errors
   for (int i = n - 1; i >= 0; i--) {
      if (Y[i] == 0) {
         Y[i] = diskToMove;
         break;
      }
   }
}