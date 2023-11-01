#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXINT INT_MAX
#define TRUE 1
#define FALSE 0

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

main()
{
	int d, i, j, k, n, r, s, minval, sum, result;
    float A[80][80];
    float p[] = {0, 0.05, 0.4, 0.08, 0.04, 0.1, 0.1, 0.23};
    n = 7;

    for (s=0; s<=(n-1); s++) {
        for (i=1; i<=n; i++) {
			minval = MAXINT;
			for (r=1; r<=i+s; r++) {
			    sum = 0;
                for (k = 1; k<=i+s; k++) {
			    	sum = (i>r-1) ? 0: A[i][r-1] + (r+1>i+s) ? 0: A[r+1][i+s];
			    }
			    if (sum < minval) minval = sum;
			}
            A[i][i+s] = minval;
		}
	}
	result = A[1][n];
}