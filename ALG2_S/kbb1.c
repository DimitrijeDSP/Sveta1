/* Foundations of Algorithms Using C++ Pseudocode Second Edition */
/* Richard E. Neapolitan , Kumarss Naimpour, PAGE 215            */
/* The Backtracking Algorithm for the 0-1 Knapsack Problem       */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

typedef struct {
    int w;
    int p;
	double ratio;
    int include;
    int bestset;
} item;

item **array;
int numbest;
int maxprofit;
int n;
int W;

typedef int (*compfn)(const void*, const void*);

int compare_item(item **i, item **j)
{
	if ((*i)->ratio < (*j)->ratio) return(1);
	if ((*i)->ratio > (*j)->ratio) return(-1);
    return(0);
}

readitems()
{
	int vi, wi, i;
	scanf("%d %d", &W, &n);

    array = (item **) malloc(sizeof(item *)*(n+1));

    i = 0;
    while(scanf("%d %d",&vi, &wi) > 0) {
	   array[i] = (item *) malloc(sizeof(item));
	   array[i]->p = vi;
	   array[i]->w = wi;
	   array[i]->ratio = (double)vi/(double)wi;
	   i++;
   }
   qsort((void *)array,n,sizeof(item *), (compfn)compare_item);
}

void knapsack (int i, int profit, int weight)
{
	int j;

    if (weight <= W && profit > maxprofit) {   /* This is best so far */
        maxprofit = profit;
        numbest = i;                           /* set numbest to number of items considered. Set bestset to this solution */
        for (j=0; j<numbest; j++)
           array[j]->bestset = array[j]->include;
    }
    if (promising(i, profit, weight) == TRUE) {
		array[i+1]->include = TRUE;            /* include w[i+1] */
		knapsack(i + 1, profit + array[i+1]->p, weight + array[i+1]->w);
		array[i+1]->include = FALSE;           /* do not include w[i+1]  */
		knapsack(i+1, profit, weight);
    }
}

int promising(int i, int profit, int weight)
{
	int j,k;
	int totweight;
	int bound;

	if (weight >= W)     /* node is promising only if we should expand to its children. */
	    return FALSE;    /* there must be some capacity left for the children */
	else {
		j = i + 1;
		bound = profit;
		totweight = weight;
		while (j < n && totweight + array[j]->w <= W) {    /* grab as many remaining items as possible  */
		    totweight = totweight + array[j]->w;           /* they are already sorted by PROFIT/WEIGHT ratio */
		    bound = bound + array[j]->p;                   /* in descend order */
		    j++;
		}
		k = j;                                      /* use k for consistency with formula in text  */
		if (k < n)
		    bound = bound + (float)(W - totweight)*(float)array[k]->p / (float)array[k]->w;   /* grab fraction of kth item  */
		return ((int) bound > maxprofit) ? TRUE: FALSE;
	}
}

/* find initial estimate                 */
/* not used here, just to control result */

int estimate()
{
    int est;
	int cap, ii, i, vi, wi;

    est = 0;
    cap = 0;
    ii=0;
    for (i=0; i<n; i++) {
		ii=i;
        vi = array[i]->p;
        wi = array[i]->w;
        if ((cap + wi) > W) break;
        cap = cap + wi;
        est = est + vi;
	}
    if (cap < W) {
		est = est + array[ii]->p * (W - cap)/array[ii]->w;
    }
    printf("est = %d\n", est);
}

main()
{
	int j;

	readitems();
	estimate();
	numbest = 0;
	maxprofit = 0;
	knapsack(-1,0,0);

    printf("maxprofit=%d\n", maxprofit);
	for (j = 0; j< numbest; j++) {
	    printf("%d ", array[j]->bestset);
	    if (j % 30 == 0) printf("\n");
	}
	printf("\n");
}

