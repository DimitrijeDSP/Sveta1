#include <stdio.h>

find_bin(unsigned int x, int *array, int n)
{
   int i;

   for (i=0; i<n; i++) {
       array[n-1-i] = (x >> i) & 1;
   }
}

main()
{
   int i, array[24];
   unsigned int x;

   x = 12582912;

   find_bin(x, array, 24);

   for (i=0; i<24; i++) {
       printf("%d ", array[i]);
   }
   printf("\n");
}

