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

int largest2(int a[], int low, int high)
{
	int s[100];
	int sn, max,max2,kk,i;

	find2max(a, low, high, s, &sn, &max);

	kk = (high-low+1)/2;
	i = 0;
	max2 = s[i];
	while (kk > 1) {
	    i++;
	    comp++;
	    if (s[i] > max2) max2 = s[i];    /* [log2(n) - 1] comparisons */
	    kk = kk/2;
	}

	return max2;
}

find2max(int a[], int low, int high, int s[], int *sn, int *max)
{
    int n, mid,i;
    int s1[100], s2[100];
    int sn1, sn2, max1, max2;

    n = high-low+1;
    *sn = 0;

    if (n == 1) {
		*max = a[0];
		*sn = 0;
		return;
    }
    if (n == 2) {
		if (a[0] >= a[1]) {
			*max = a[0];
			s[*sn++] = a[1];
            return;
		}
	    else {
			*max = a[1];
			s[*sn++] = a[0];
            return;
		}
    }
    /* we know that n>=3 */
    mid = (high + low)/2;
    find2max(a, low, mid, s1, &sn1, &max1);
    find2max(a, mid+1, high, s2, &sn2, &max2);
    if (max1 >= max2) {
		*max = max1;
		for (i=0; i<sn1; i++)
		    s[*sn++] = s1[i];
		s[*sn++] = max2;
    }
    else {
		*max = max2;
		for (i=0; i<sn2; i++)
		    s[*sn++] = s2[i];
		s[*sn++] = max1;
	}
	return;
}

#define MAX 100001


void main(int argc, char *argv[])
{
	int i,j,count,max2;
	int o[MAX];
	char x[10];

    comp = 0;
    count = 0;
    printf("--------------------------\n");
    printf("--------- INPUT ----------\n");
    printf("--------------------------\n");
    while (scanf("%s\n",x) != EOF) {
       o[count] = atoi(x);
       printf ("o[%d]=%d\n",count, o[count]);
       count ++;
	}

    max2 = largest2(o,0,count-1);
    printf ("second largest is %d\n", max2);
    printf ("n=%d comp=%d shold be %d\n", count, comp, count+log2x(count)-2);
    printf ("log2x(%d)=%d\n", count,log2x(count));
}