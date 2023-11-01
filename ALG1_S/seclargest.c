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


int largest2(int a[], int k)
{
     int i,kk, temp, max2;

     for (i=0; i<k; i++) printf("%4d ",a[i]); printf("\n");

     kk = k/2;
     while (kk > 0) {
		 for (i=0; i<kk; i++) {
			 comp++;
             if (a[i+kk] > a[i]) {    /* [n - 1] comparisons */
                 temp = a[i];
                 a[i] = a[i+kk];
                 a[i+kk] = temp;
		     }
	     }
         for (i=0; i<k; i++) printf("%4d ",a[i]); printf("\n");
         kk = kk/2;
     }

     kk = k/2;
     i = 1;
     max2 = a[i];
     while (kk > 1) {
        i++;
        comp++;
        if (a[i] > max2) max2 = a[i];    /* [log2(n) - 1] comparisons */

        kk = kk/2;
     }

     return max2;
}

#define MAX 100001


void main(int argc, char *argv[])
{
	int i,j,count, mm;
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

    mm = largest2(o,count);
    printf ("second largest is %d\n", mm);
    printf ("n=%d comp=%d shold be %d\n", count, comp, count+log2x(count)-2);
    printf ("log2x(%d)=%d\n", count,log2x(count));
}