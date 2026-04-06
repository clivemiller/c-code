#include <stdio.h>
#include <stdlib.h>

int moveCount = 0;

void move(char from, char to) {
    moveCount++;
    printf("Move %c TO %c\n", from, to);
}

void restrictedHanoi(int n, char from, char to, char backup) {
   if (n == 0) return;
    
   if ((from == 'A' && to == 'C') || (from == 'C' && to == 'A')) {
      // Step 1: Move n-1 disks from A to C
      restrictedHanoi(n - 1, from, to, backup);
      // Step 2: Move disk n from A to B
      move(from, backup);
      // Step 3: Move n-1 disks from C to A
      restrictedHanoi(n - 1, to, from, backup);
      // Step 4: Move disk n from B to C
      move(backup, to);
      // Step 5: Move n-1 disks from A to C
      restrictedHanoi(n - 1, from, to, backup);
   } else {
      // Adjacent pegs: A<->B or B<->C
      restrictedHanoi(n - 1, from, backup, to);
      move(from, to);
      restrictedHanoi(n - 1, backup, to, from);
   }
}

int main(int argc, char *argv[]) {   
   int n = 0;
   if (argc > 1) {
      n = atoi(argv[1]);
   }
    
   restrictedHanoi(n, 'A', 'C', 'B');
    
   return 0;
}
