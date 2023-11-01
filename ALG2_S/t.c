#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* DYNAMIC PROGRAMMING VERSION            */
/* RETURNS OPTIMAL VALUE, NO BACKTRACKING */

#define MAXINT INT_MAX
#define TRUE 1
#define FALSE 0

#define MAX(a,b) (((a)>(b))?(a):(b))

listmatrix(int **a, int n, int W)
{
	int i, x;

	    printf("===========================\n");
	    for (i=0; i<=n; i++) {
	        for (x=0; x<=W; x++) {
	             printf("%3d ", a[i][x]);
		    }
		    printf("\n");
		}
		printf("===========================\n");
}

main()
{
	int W, n, vi, wi, i, x;
	scanf("%d %d", &W,&n);
    int **A, *vx, *wx;

    /*  int A[n,W];  */
    A = (int **) malloc((n+1)*sizeof(int *));
    for(i=0; i<(n+1); i++) {
        A[i] = (int *) malloc((W+1)*sizeof(int));
        for(x=0; x<=W; x++) A[i][x] = -1;
	}

    vx = (int *) malloc((n+1)*sizeof(int));
    wx = (int *) malloc((n+1)*sizeof(int));


    for(x=0; x<=W; x++) {
        A[0][x] = 0;
    }

    for (i=1; i<=n; i++) {
		if (scanf("%d %d",&vi, &wi) <= 0) continue;
		vx[i] = vi;
		wx[i] = wi;
    }

        for (x=0; x<=W; x++) {
    for (i=1; i<=n; i++) {
		    if (wx[i] > x) {
				A[i][x] = A[i-1][x];
			}
		    else {
			    A[i][x] = MAX(A[i-1][x],A[i-1][x-wx[i]]+vx[i]);
			}
	    }
	}

	printf("A[%d][%d]=%d\n", n, W, A[n][W]);
}