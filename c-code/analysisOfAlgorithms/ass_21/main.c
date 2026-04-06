/*********************************************
 * Id: mill0999
 *
 * permutations
 *********************************************/
#include <stdio.h>
#include <stdlib.h>

// Permutations.

// Write a program that takes a single integer as input (n) and returns all
// permutations of the characters from 1 to n each on its own line.

// For example:
// ./permutations 3
// 123
// 132
// 213
// 231
// 312
// 321

// Function to swap two characters */
void swap(char *x, char *y) {
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

// Function to generate all permutations of the string
void permute(char *a, int l, int r) {
    int i;
    if (l == r) {
        printf("%s\n", a); // Base case: a permutation is found
    } else {
        for (i = l; i <= r; i++) {
            swap((a + l), (a + i));      // Swap
            permute(a, l + 1, r);        // Recurse for the remaining part
            swap((a + l), (a + i));      // Backtrack (swap back)
        }
    }
}

void perms(int n) {
    char numbers[n];

    for (int i = 0; i < n; i++) {
        numbers[i] = (i + 1) + '0';  // Convert integer to character
    }
    numbers[n] = '\0';  // Null terminate the string

    permute(numbers, 0, n - 1);
}

int main(int argc, char *argv[])
{
   int n = atoi(argv[1]);

   perms(n);
   return 0;
}
