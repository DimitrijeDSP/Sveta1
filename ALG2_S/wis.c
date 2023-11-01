#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXINT INT_MAX
#define TRUE 1
#define FALSE 0

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAX 1000

main ()
{
    int s;
    int A[MAX];

    A[0] = 0;
    A[1] = w1;
    for (i = 2; i<=n; i++) {
        A[i] = MAX( A[i - 1] , A[i - 2] + wi );
    }

    s = 0;
    while (i >= 1) {                       /* scan through array from right to left   */
        if (A[i - 1] >= A[i - 2] + wi) {   /* i.e. case 1 wins                        */
            i=i-1;
		}
        else {                             /* i.e. case 2 wins                        */
           - Add vi to s
           i=i-2;
        }
	}
}