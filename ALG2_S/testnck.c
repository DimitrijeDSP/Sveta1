#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned nck(unsigned n, unsigned k)  /* n choose k */
{
    int i;
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    int result = n;
    for( i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

main()
{
	int i, j;
     printf("3C4=%d\n", nck(3,4));
     printf("3C3=%d\n", nck(3,3));
     printf("3C2=%d\n", nck(3,2));
     printf("3C1=%d\n", nck(3,1));
     printf("3C0=%d\n", nck(3,0));

     for (i=1; i<=3; i++) {
		 j = nck(3, i);
          printf("3C%i=%d --- %d * %d = %d\n", i, j, i, j, i*j);
     }

     for (i=1; i<=24; i++) {
		 j = nck(24, i);
          printf("24C%i=%d --- %d * %d = %d\n", i, j, i, j, i*j);
     }
}