/* Foundations of Algorithms Using C++ Pseudocode Second Edition */
/* Richard E. Neapolitan , Kumarss Naimpour, PAGE 120            */
/* Algorithm 3.9 - Optimal binary search tree                    */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXINT 100000.0
#define TRUE 1
#define FALSE 0

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))


/*
void optsearchtree(int n, const float *p, float *minavg, int **R)
*/
void optsearchtree(int n, const float *p, float *minavg)
{
	int i,j,k, diagonal, kmin,s;
	float A[n+2][n+2], minval, sum;

    for (i=1; i<=n; i++) {
		A[i][i-1] = 0;
		A[i][i] = p[i];
/*
		R[i][i] = i;
		R[i][i-1] = 0;
*/
    }
    A[n+1][n] = 0;
 /*

    R[n+1][n] = 0;
 */

     for (diagonal=1; diagonal<=(n-1); diagonal++) {
        for (i=1; i<=n-diagonal; i++) {
			j = i + diagonal;

			minval = MAXINT;
            for (k = i; k<=j; k++) {
				sum = A[i][k-1] + A[k+1][j];
                if (sum < minval) {
					minval = sum;
					kmin = k;
				}
			}
			sum = p[i];
			for (s=i+1; s<=j; s++) {
				sum = sum + p[s];
			}
            A[i][j] = minval + sum;
/*
			R[i][j] = kmin;
*/
		}
	}
	*minavg = A[1][n];
}

main()
{
	int d, i, j, k, n, r, s, sum, result;
    const float p[] = {0, 0.2, 0.05, 0.17, 0.1, 0.2, 0.03, 0.25};
    float minval;

    n = 7;

   optsearchtree(n, p, &minval);
   printf("minval=%f\n", minval);
}

