
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define DEBUG 0
#define MAX(a,b) (((a)>(b))?(a):(b))

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

int bbfun(item **a, int n, int i, int value, int room, int estimate)
{
	int val1, val2, val, result;
	int value1, room1, estimate1, value2, room2, estimate2;
    static  int bestsol;

    if (DEBUG) printf("i=%d value=%d room=%d estimate=%d\n", i, value, room, estimate);
    if (i == -1) bestsol = 0;

    if (room < 0) {
        if (DEBUG) printf("LEFT STOP\n");
        return (0);
	}

    if (estimate < bestsol) {
        if (DEBUG) printf("RIGHT STOP\n");
        return (0);
	}

    if (i + 1 >= n) {
        if (DEBUG) printf ("--------------------------------------------- value=%d bestsol=%d\n", value, bestsol);
		if (value > bestsol) bestsol = value;
        if (DEBUG) printf("**** BRANCH END ****\n");
        return (0);
	}

    /* GO LEFT, TAKE ITEM */
    value1 = value + a[i+1]->value;
    room1 = room - a[i+1]->weight;
    estimate1 = estimate;
    if (DEBUG) printf("LEFT GO\n");
    val1 = bbfun(a, n, i+1, value1, room1, estimate1);  /* take next item         */

    /* GO RIGHT, SKIP ITEM */
    value2 = value;
    room2 = room;
    estimate2 = estimate - a[i+1]->bound;
    if (DEBUG) printf("RIGHT GO\n");
    val2 = bbfun(a, n, i+1, value2, room2, estimate2);  /* do not take next item  */

    val = val1;
    if (val2 > val1) val = val2;
    bestsol = bestsol + val;
    if (DEBUG) printf ("bestsol=%d\n", bestsol);

    if (i == -1)
        return bestsol;
    else
        return val;
}

main()
{
	int W, n, i, vi, wi, ri, est, cap, ii, optval;
    item **array, **array1;

	scanf("%d %d", &W,&n);

    array = (item **) malloc(n*sizeof(item *));
    array1 = (item **) malloc(n*sizeof(item *));

    for (i=0; i<n; i++) {
		if (scanf("%d %d",&vi, &wi) <= 0) continue;
        array[i] = malloc(sizeof(item));
        array[i]->value = vi;
        array[i]->weight = wi;
        array[i]->ratio = (double)vi/(double)wi;
        array[i]->bound = 0;
        array1[i] = array[i];
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


    optval = bbfun(array1, n, -1, 0, W, est);
    printf("OPTVAL = %d \n", optval);
}