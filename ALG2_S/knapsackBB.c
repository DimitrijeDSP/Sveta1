/* BRANCH AND BOUND VERSION               */
/* RETURNS OPTIMAL VALUE, NO BACKTRACKING */

/* 0.  I sort the items once by decreasing value/ weight,
       before doing anything else, and then never sort again.

   1.  The key to branch and bound is being able quickly estimate
       an upperbound on the solution you're working on, and if it's
       less than the best solution you've seen so far, you just back track.
       So how do you find an upper bound on the knapsack problem?
       You take items in decreasing order of value/weight, and if you get
       to an item that's too large fit in your remaining capacity, you allow
       yourself to take a "chunk" of it, with value proportional
       to the weight fraction of the object that you're putting into
       the knapsack.  This gives us a value which is >= the best possible
       value.

   2.  Then branch and bound function is recursive, and quite simple.
       I maintain the best value so far as a static variable.
       The branching happens in recursive calls, so the skeleton of
       the function is something like:

       int    my_function(  state variables, e.g. index, capacity, value)  {
          static   best solution;

          // a. check things like index bounds

          // b. check if upper bound on remaining items enough
                to exceed best known solution together with value
                we have now

          return max( my_function( index incremented, item not taken),
                      my_function(index incremented, item taken));
       }
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXINT INT_MAX
#define TRUE 1
#define FALSE 0

#define MAX(a,b) (((a)>(b))?(a):(b))

int level;

typedef int (*compfn)(const void*, const void*);

typedef struct {
	int value;
	int weight;
	double ratio;
	int bound;
} item;

int compare_item(item **i, item **j)
{
	if ((*i)->ratio < (*j)->ratio) return(1);
	if ((*i)->ratio > (*j)->ratio) return(-1);
    return(0);
}

char *padchar(int level)
{
    int k;
    char *p;
    int tab = 1;
    p = malloc(sizeof(char)*tab*level);
    for (k=0; k<level*tab;k++) {
        p[k] = ' ';
	}
	p[tab*level-1] = '\0';
	return p;
}

/* i - current item to analyze */
/* ev - value achieved so far   */
/* cc - capacity left so far    */

int bbfun(item **a, int n, int i, int ev, int cc)
{
	int val1, val2, result;
    static  int bestsol;

    level++;

    printf("%sBBFUN level=%d bestsol=%d i=%d ev=%d cc=%d\n", padchar(level), level, bestsol, i, ev, cc);

    if (i == 0) bestsol = 0;
    if (i < 0 || i >= n ) {
		printf("%s######### i=%d out of bounds\n", padchar(level), i);
		level --;
		return -1;
	}

    if (cc - a[i]->weight < 0) {
		printf("%s$$$$ capacity error (%d) for i=%d\n", padchar(level), cc - a[i]->weight, i);
        val2 = -1;
	}
    else {
		bestsol = bestsol + a[i]-> value;
		printf("%s$$$$ go LEFT from i=%d to i=%d\n", padchar(level), i, i+1);
        val2 = bbfun(a, n, i+1, ev, cc - a[i]->weight);  /* take current item         */
    }

    if (ev - a[i]->value < bestsol) {
		printf("%s$$$$ estimate error (%d) for bestsol=%d i=%d\n", padchar(level), ev - a[i]->value, bestsol, i);
        val1 = -1;
	}
    else {
		printf("%s$$$$ go RIGHT from i=%d to i=%d\n", padchar(level), i, i+1);
        val1 = bbfun(a, n, i+1, ev - a[i]->value, cc);   /*  do not take current item */
    }

    printf("%s----- val1=%d val2=%d\n", padchar(level), val1, val2);
    if (val1 > 0 && val1 > val2) {
	   printf("%sSKIP %d\n", padchar(level), i);
       bestsol = val1 + bestsol;
    }
    if (val2 > 0 && val2 > val1) {
	   printf("%sTAKE %d\n", padchar(level), i);
       bestsol = a[i]->value + bestsol;
    }
    level--;
    return bestsol;
}


main()
{
	int W, n, i, vi, wi, ri, est, cap, ii, optval;
    item **array;

    level = 0;
	scanf("%d %d", &W,&n);

    array = (item **) malloc(n*sizeof(item *));

    for (i=0; i<n; i++) {
		if (scanf("%d %d",&vi, &wi) <= 0) continue;
        array[i] = malloc(sizeof(item));
        array[i]->value = vi;
        array[i]->weight = wi;
        array[i]->ratio = (double)vi/(double)wi;
        array[i]->bound = 0;
	}

    qsort((void *)array,n,sizeof(item *), (compfn)compare_item);

    printf("%d %d\n", W, n);
    for (i=0; i<n; i++) {
        printf("%d %d %f\n", array[i]->value, array[i]->weight, array[i]->ratio);
	}

/* found initial estimate */

    est = 0;
    cap = 0;
    ii=0;
    for (i=0; i<n; i++) {
		ii=i;
        vi = array[i]->value;
        wi = array[i]->weight;
        if ((cap + wi) > W) break;
        cap = cap + wi;
        est = est + vi;
        array[i]->bound = vi;
	}
    if (cap < W) {
		array[i]->bound = array[ii]->value * (W - cap)/array[ii]->weight;
		est = est + array[ii]->bound;
    }
    printf("est = %d\n", est);


    optval = bbfun(array, n, 0, est, W);
    printf("OPTVAL = %d \n", optval);
}