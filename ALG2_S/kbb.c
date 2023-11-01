#include <stdio.h>

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

    array[0] = (item *) malloc(sizeof(item));
	array[0]->p = vi;
	array[0]->w = wi;
	array[0]->ratio = 0.0;
    i = 1;
    while(scanf("%d %d",&vi, &wi) > 0) {
	   array[i] = (item *) malloc(sizeof(item));
	   array[i]->p = vi;
	   array[i]->w = wi;
	   array[i]->ratio = (double)vi/double(wi);
	   i++;
   }
}

void knapsack (int i, int profit, int weight)
{
	int j;

	printf("i=%d profit=%d weight=%d\n", i, profit, weight);

    if (weight <= W && profit > maxprofit) {   /* This is best so far */
        maxprofit = profit;
        numbest = i;                           /* set numbest to number of items considered. Set bestset to this solution */
        for (j=0; j<=numbest; j++)
           bestset[j] = include[j];
    }
    if (promising(i, profit, weight) == TRUE) {
		include[i+1] = TRUE;            /* include w[i+1] */
		knapsack(i+1, profit+p[i+1], weight+w[i+1]);
		include[i+1] = FALSE;               /* do not include w[i+1]  */
		knapsack(i+1, profit, weight);
    }
}

int promising(int i, int profit, int weight)
{
	int j,k;
	int totweight;
	float bound;

	if (weight >= W)     /* node is promising only if we should expand to its children. */
	    return FALSE;    /* there must be some capacity left for the children */
	else {
		j = i + 1;
		bound = profit;
		totweight = weight;
		while (j <= n && totweight + w[j] <= W) {    /* grab as many items as possible  */
		    totweight = totweight + w[j];
		    bound = bound + p[j];
		    j++;
		}
		k = j;                                      /* use k for consistency with formula in text  */
		if (k<=n)
		    bound = bound + (float)(W-totweight)*(float)p[k]/(float)w[k];   /* grab fraction of kth item  */
		printf("bound=%d maxprofit=%d\n", (int) bound, maxprofit);
		return ((int)bound > maxprofit) ? TRUE: FALSE;
	}
}

main()
{
	int j;
	  readitems();
	  numbest = 0;
	  maxprofit = 0;
	  knapsack(0,0,0);
	  printf("maxprofit=%d\n", maxprofit);
	  for (j = 1; j<= numbest; j++)
	      printf("%d ", bestset[j]);
	  printf("\n");
}