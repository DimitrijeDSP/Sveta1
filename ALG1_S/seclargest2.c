#include <stdio.h>

int comp;

int log2x(int x)
{
	int i,xx;
	xx=x;
	i=-1;
	while (xx > 0) {
		xx = xx/2;
		i++;
    }
    return (i);
}

swap(int a[], int i, int j, int size)
{
	int k, temp;
	k = 0;
	for (k=0; k<size; k++) {
		temp = a[i+k];
		a[i+k] = a[j+k];
		a[j+k] = temp;
    }
}

int largest2(int a[], int i, int size)
{
	int max,max2,j,k;

	max = find2max(a, i, size);
    j = i+1;
    k = 1;
	max2 = a[j];
	while (k < log2x(size)) {
	    j=j*2;
	    comp++;
	    if (a[j] > max2) max2 = a[j];    /* [log2(n) - 1] comparisons */
	    k++;
	}
	return max2;
}

int find2max(int a[], int i, int size)
{
	int max,max1,max2,ii,j,half;

    printf("======= enter findmax: i=%d, size=%d ============\n", i, size);
    for (ii=i;ii<i+size;ii++) printf("%d ",a[ii]); printf("\n");
    if (size < 2) return -1;

    half = size/2;
	j = i + half;
    max = a[i];

    if (size == 2) {
		max1 = a[i];
		max2 = a[j];
    }
    if (size > 2) {
        max1 = find2max(a, i, half);   /* n - 1 comparisons */
        max2 = find2max(a, j, half);
    }
    comp++;
    if (max2 >= max1) {
		max = max2;
		swap(a,i,j,half);
    }
	return max;
}

#define MAX 100001


void main(int argc, char *argv[])
{
	int i,j,count,max2;
    char x[10];
	int o[MAX];

    comp = 0;
    count = 0;
    printf("--------------------------\n");
    printf("--------- INPUT ----------\n");
    printf("--------------------------\n");
    while (scanf("%s\n",x) != EOF) {
       o[count] = atoi(x);
       count ++;
	}
    for (i=0;i<count;i++) printf("%d ",o[i]); printf("\n");

    max2 = largest2(o,0,count);
    printf("--------------------------\n");
    printf("--------- OUTPUT ---------\n");
    printf("--------------------------\n");
    for (i=0;i<count;i++) printf("%d ",o[i]); printf("\n");
    printf ("second largest is %d\n", max2);
    printf ("n=%d comp=%d shold be %d\n", count, comp, count+log2x(count)-2);
    printf ("log2x(%d)=%d\n", count,log2x(count));
}