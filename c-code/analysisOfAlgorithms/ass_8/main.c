/*********************************************
 * Id: mill0999
 *
 * brute-force string matching algorithm to find all occurrences of a pattern a string.
 *********************************************/
#include <stdio.h>
#include <stdlib.h>

// Brute-force string matching algorithm
int BruteForceStringMatch(char text[], char pattern[], int n, int k, int start) {
   for (int i = start; i <= n-k; i++) {
      int j = 0;
      while (j < k && pattern[j] == text[i+j]) {
         j++;
      }

      if (j == k) {
         return i;
      }
   }

   return -1;
}

// Helper function to print a character array
void printCharArray(char charArray[], int n) {
   for (int i = 0; i < n; i++) {
      putchar(charArray[i]);
   }
   printf("\n");
}

// Helper function to count the length of a character array
int countLength(char charArray[]) {
   int count = 0;
   while (charArray[count] != '\0') {
      count++;
   }

   return count;
}

int main(int argc, char *argv[]) {     
   int k = countLength(argv[1]);  // pattern length (short)
   int n = countLength(argv[2]);  // text length (long)
   int matches[n];

   char pattern[k];
   for (int i = 0; i < k; i++) {
      pattern[i] = argv[1][i];
   }

   char text[n];
   for (int i = 0; i < n; i++) {
      text[i] = argv[2][i];
   }

   // Print the pattern and text
   int offset = 0;
   int found = 0;
   int result;

   // Search for pattern in text and store the locations of matches
   while ((result = BruteForceStringMatch(text, pattern, n, k, offset)) != -1)
   {
      // Store the location of the match
      matches[found] = result;
      found++;
      // Update the offset to search for the next match
      offset = result + 1;
   }

   // Print the locations of matches
   printf("Matches found at locations: ");
   for (int i = 0; i < found; i++) {
      if (i = found-1) {
         printf("%d", matches[i]);
      } else {
         printf("%d ", matches[i]);
      }
   }
   printf("\n");
   
   return 0;
}