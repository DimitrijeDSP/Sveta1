#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* DYNAMIC PROGRAMMING VERSION, COMPRESSED */
/* RETURNS OPTIMAL VALUE, NO BACKTRACKING  */

#define MAXINT INT_MAX
#define TRUE 1
#define FALSE 0

#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct {
	int min;
	int max;
	int val;
	struct item *next;
} item;


printitems(item **a, int n)
{
	item *p;
	int x, i;

	printf("---------- %d -----------\n", n);
    for (i=0; i<=n; i++) {
	   p = a[i];
	   printf("%d: ", i);
	   while (p != NULL) {
           printf("[%d|%d:%d] ", p->val, p->min,p->max);
	       p = (item *)p->next;
	   }
	   printf("\n");
    }
}

listitems(item **a, int x, int y)
{
	int i, j;

	printf("---------- %d %d -----------\n", x, y);
    for (i=0; i<=x; i++) {
        for (j=0; j<=y; j++) {
           printf("%3d ", getitem(a,i,j));
	   }
	   printf("\n");
    }
}

int getitem(item **a, int i, int j)
{
	item *p;
	int x;

	x = -1;
	p = a[i];
	while (p != NULL) {
		if (p->max >= j && p->min <= j) {
	  	    x = p->val;
		    break;
	    }
	    p = (item *)p->next;
	}
	return x;
}

item *finditem(item **a, int i, int v)
{
	item *p;

	p = a[i];
	while (p != NULL) {
		if (p->val == v) return p;
	    p = (item *)p->next;
	}
	return NULL;
}

item *setitem(item **a, int i, int j, int v)
{
	item *p, *q;

	p = a[i];

    /* no items yet */
	if (p == NULL ) {
		p = malloc (sizeof(item));
        p->min = 0;
        p->max = j;
        p->val = v;
        p->next = NULL;
        return p;
	}

    p = finditem(a, i, v);
    if (p != NULL) {
		if (p->next == NULL || a[i] == p) {
		    p->max = j;
		}
		return a[i];
	}
	else {
		q = malloc (sizeof(item));
        q->max = j;
        q->min = (a[i]->max)+1;
        q->val = v;
        q->next = (struct item *)a[i];
		return q;
    }
}

item **inititems(int n)
{
	int i;
	item **x;

    x = (item **) malloc((n+1)*sizeof(item *));
    for (i=0; i<=n; i++) {
		x[i] = NULL;
    }
    return x;
}

main()
{
	int W, n, vi, wi, i, x, t1, t2;
    item **A;
    item *p;

	scanf("%d %d", &W,&n);

    A = inititems(n);

    A[0] = setitem(A,0,W,0);

    for (i=1; i<=n; i++) {
		if (scanf("%d %d",&vi, &wi) <= 0) continue;
		printf("%d/%d\n", i, n);
        for (x=0; x<=W; x++) {
		    if (wi > x) {
				t1 = getitem(A,i-1,x);
		        A[i] = setitem(A,i,x,t1);
				t1 = getitem(A,i,x);
			}
		    else {
		        A[i] = setitem(A,i,x,MAX(getitem(A,i-1,x),getitem(A,i-1,x-wi)+vi));
		    }
	    }
	}
/*
	printitems(A, n);
	listitems(A, n, W);
*/
	printf("A[%d][%d]=%d\n", n, W, getitem(A,n,W));
}