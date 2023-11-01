#include <stdlib.h>
#include <stdio.h>

int comp;
int mode;

typedef int item_type;

swap(item_type *x, item_type *y)
{
	item_type t;
	t = *x;
	*x = *y;
	*y = t;
}

quicksort(item_type s[], int l, int h)
{
	int p;            /* index of partition */
	int m, mm;        /* median */

    if ((h-l) > 0) {
        if (mode == 1) swap(&s[l], &s[h]);
        if (mode == 2) {
			m = l+(h-l)/2;
			if (s[l] < s[h]) {
				if (s[l] < s[m] && s[m] < s[h]) mm = m;
				if (s[m] <= s[l]) mm = l;
				if (s[h] <= s[m]) mm = h;
			}
			if (s[l] > s[h]) {
				if (s[h] < s[m] && s[m] < s[l]) mm = m;
				if (s[m] <= s[h]) mm = h;
				if (s[l] <= s[m]) mm = l;
			}
            swap(&s[l], &s[mm]);
		}
		p = partition(s,l,h);
		quicksort(s,l,p-1);
		quicksort(s,p+1,h);
    }
}

int partition(int a[], int l, int r)
{
	int i;          /* split between low and high */
	int j;          /* split between partitioned and unpartitioned */
	int p;          /* pivot element value */

    comp += r-l;
	p = a[l];
	i = l+1;
	for (j=l+1; j<=r; j++)
	    if (a[j] < p) {
			swap(&a[j], &a[i]);
			i++;
	    }
	swap(&a[l], &a[i-1]);

	return(i-1);
}


#define MAX 100001


void main(int argc, char *argv[])
{
	int i,j,count,max2;
    char x[10];
	int o[MAX];

    mode=0;
    if (argc == 2) mode=atoi(argv[1]);
    comp = 0;
    count = 0;
/*
    printf("--------------------------\n");
    printf("--------- INPUT ----------\n");
    printf("--------------------------\n");
*/
    while (scanf("%s\n",x) != EOF) {
       o[count] = atoi(x);
       count ++;
	}
 /*
    for (i=0;i<count;i++) printf("%d\n",o[i]);
 */

    quicksort(o,0,count-1);
/*
    printf("--------------------------\n");
    printf("--------- OUTPUT ---------\n");
    printf("--------------------------\n");
    for (i=0;i<count;i++) printf("%d\n",o[i]);
*/
    printf("mode=%d comp=%d\n",mode, comp);
}