/* ====================================================== */
/*                                                        */
/*    INPUT 564 3 456 33 1 34 35 32 444 8 33 22           */
/*                                                        */
/*    ================================================    */
/*    HEAP (ROOT MAX) elements 12                         */
/*    ================================================    */
/*                                                        */
/*    0:                564                               */
/*    2:           444         456                        */
/*    4:        33    33    34      35                    */
/*    8:       3 32  1 8   22                             */
/*                                                        */
/*    ================================================    */
/*    HEAP (ROOT MIN) elements 12                         */
/*    ================================================    */
/*                                                        */
/*    0:                        1                         */
/*    2:               3              22                  */
/*    4:           32      8       34     35              */
/*    8:        564 444  33 33   456                      */
/*                                                        */
/* ====================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0

#define ROOTMIN 0
#define ROOTMAX 1

#define MAXINT INT_MAX
#define DEBUG FALSE

#define HEAPMAX 20000

typedef struct {  /* HEAP STRUCTURE                         */
	int nh;       /* # elements in heap                     */
	int *hv;      /* heap array , starts at index 0         */
	int t;        /* heap type (0 - root min; 1 - root max) */
} heap;

inith(heap *h, int type)
{
	h->hv = malloc((HEAPMAX+1)*sizeof(int));
	h->nh=0;
	h->t = type;
}

int geth(heap *h, int ix) /* public index 1..nh */
{
    return(h->hv[ix-1]);
}


int outord(heap *h, int ix, int iy)  /* public index 1..nh ix=child, iy=parent */
{
    if ((geth(h,ix) < geth(h,iy) && h->t == ROOTMIN) ||
        (geth(h,ix) > geth(h,iy) && h->t == ROOTMAX))
        return TRUE;
    else
        return FALSE;
}

bubbleup(heap *h, int ix) /* change bottom -> root */
{                         /* public index 1..nh   */
	int x,ixp;

    ixp = parent(h,ix);
    if (ixp == -1) return;  /* root */
    if (outord(h,ix,ixp) == TRUE)   {
        swap(h,ix,ixp);
        bubbleup(h,ixp);      /* recurse */
    }
}

swap(heap *h, int ix, int iy) /* public index 1..nh */
{
	int x;

    x = h->hv[ix-1];
    h->hv[ix-1] = h->hv[iy-1];
    h->hv[iy-1] = x;
}

int parent(heap *h, int ix) /* public index 1..nh */
{
	int i;
	i = (int) ix/2;
	if (ix == 1) i = -1;
	return(i);
}

int child(heap *h, int ix) /* public index 1..nh */
{
	int i;
	i = ix*2;
	if (i > h->nh) i = -1;
	return(i);
}

readh(heap *h, char *file)
{
    FILE *in;
    int count, hash, x;

    in = fopen(file, "r");
    count=0;
    while (fscanf(in,"%d",&x) != EOF)
        puth(h,x);
    fclose(in);
}

puth(heap *h, int x) /* put value at the end of heap */
{
	if (h->nh > HEAPMAX) {
		printf("heap insert overflow\n");
		return;
	}
    h->hv[h->nh++] = x;
    bubbleup(h,h->nh);  /* pass public index (internal+1) */
}

printh(heap *h) /* traverse heap and print piramide */
{
    int i,j,k;
    char *a[] = {"ROOT MIN","ROOT MAX"};

    printf("================================================\n");
    printf("HEAP (%s) elements %d\n", a[h->t], h->nh);
    printf("================================================\n");
    j=0;
    k=0;
	printf("\n%d: ",j);
    for (i=0; i<h->nh; i++) {
		printf("%d ", h->hv[i]);
		if (k == j) {
		    j = j*2;
		    if (j == 0) j = 2;
		    k = 0;
			printf("\n%d: ",j);
		}
		k++;
	}
	printf("\n\n");
}


int extract(heap *h)     /* extract root element (min or max) */
{
	int x = -1;
	if (h->nh > 0) {
		x = h->hv[0];
		if (h->nh > 1)
		    h->hv[0] = h->hv[h->nh -1];
		h->nh--;
		bubbledown(h,1);    /* pass public index (internal+1) */
	}
	return x;
}

bubbledown(heap *h, int ix)    /* public index 1..nh */
{
	int ic, imin;

	ic = child(h,ix);
	if (ic == -1) return;
	imin = ix;

    if (ic < h->nh)           /* consider lower child */
       if (outord(h, ic+1, ic)) ic = ic+1;

    if (outord(h,ic,ix) == TRUE)   {
        swap(h,ic,ix);
        bubbledown(h,ic);      /* recurse */
    }
}

sortprint(heap *h)
{
	int i;
    char *a[] = {"ROOT MIN","ROOT MAX"};

    printf("================================================\n");
    printf("HEAP (%s) elements %d\n", a[h->t], h->nh);
    printf("================================================\n");

    while(h->nh > 0)
        printf("%d ", extract(h));
    printf("\n\n");
}

main(int argc, char *argv[])
{
	heap hmin, hmax;

    if (argc != 2) { printf("enter heap input file name\n"); return; }

    inith(&hmin, ROOTMIN);
	readh(&hmin, argv[1]);
	printh(&hmin);
	sortprint(&hmin);

    inith(&hmax, ROOTMAX);
	readh(&hmax, argv[1]);
	printh(&hmax);
    sortprint(&hmax);
}

