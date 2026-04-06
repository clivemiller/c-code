#include <stdio.h>

int gcd(int m, int n) {
   if (n == 0) {
      return m;
   }

   int mod = m % n;
   gcd(n, mod);
}

void main() {
   int * m;
   int * n;

   printf("%s", "Enter m: ");
   scanf("%d", m);

   printf("%s", "Enter n: ");
   scanf("%d", n);

   printf("The greatest Common Denominator is: %d\n", gcd(*m, *n));
}
