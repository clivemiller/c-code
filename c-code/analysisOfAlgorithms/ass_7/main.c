/*********************************************
 * Id: mill0999
 *
 * cyclic hanoi
 *********************************************/
#include <stdio.h>
#include <stdlib.h>

void hanoi(int n, int from, int dir)
{
   if (n == 0) return;

   /* dir=0: to=from+1, aux=from+2 ; dir=1: to=from+2, aux=from+1 */
   int to  = (from + 1 + dir) % 3;
   int aux = (from + 2 - dir) % 3;

   if (dir == 0) {
       hanoi(n - 1, from, 1);
       printf("Move %c TO %c\n", 'A' + from, 'A' + to);
       hanoi(n - 1, aux, 1);
   } else {
       hanoi(n - 1, from, 1);
       printf("Move %c TO %c\n", 'A' + from, 'A' + aux);
       hanoi(n - 1, to, 0);
       printf("Move %c TO %c\n", 'A' + aux, 'A' + to);
       hanoi(n - 1, from, 1);
   }
}

int main(int argc, char *argv[])
{
   int n = atoi(argv[1]);

   // move all disks from A(0) to C(2): long direction
   hanoi(n, 0, 1);
   return 0;
}
