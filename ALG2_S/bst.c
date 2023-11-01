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
    int A[80][80];
    int p[] = {0, 0.05, 0.4, 0.08, 0.04, 0.1, 0.1, 0.23};
    n = 7;

    for (i=1; i<=n; i++) {
		A[i][i-1] = 0;
		A[i][i] = p[i];
/*		R[i][i] = i;   */
    }
    A[n+1][n] = 0;
    for (d=1; d<=(n-1); d++) {
        for (i=1; i<=n-d; i++) {
			j=i+d;
			minval = MAXINT;
            for (k = i; k<=j; k++) {
				sum = A[i][k-1] + A[k+1][j];
                if (sum < minval) {
					minval = sum;
				/*	kmin = k;   */
				}
			}
/*			R[i][j] = kmin;   */
			sum = p[i];
			for (s=i+1; s<=j; s++) {
				sum = sum + p[s];
			}
            A[i][j] = minval + sum;
		}
	}
	result = A[1][n];
	printf("result=%d\n", result);
}