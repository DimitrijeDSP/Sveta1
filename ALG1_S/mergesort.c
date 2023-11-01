#include <stdio.h>

#define MAX 100001

double tran;

mergesort(int a[], int low, int high)
{
	int mid;
	if(low<high)
	{
		mid=(low+high)/2;
		mergesort(a,low,mid);
		mergesort(a,mid+1,high);
		merge(a,low,high,mid);
	}
	return(0);
}

merge(int a[], int low, int high, int mid)
{
	int i, j, k, c[MAX];
	i=low;
	j=mid+1;
	k=low;
	while((i<=mid)&&(j<=high))
	{
		if(a[i]<a[j]) {
			c[k]=a[i];
			k++;
			i++;
		}
		else {                                /* piggytail on mergesort                     */
            tran = tran + (double)(mid+1-i);  /* count transitions                          */
			c[k]=a[j];                        /* if insert from right part, add number of   */
			k++;                              /* unprocessed from left part                 */
			j++;
		}
	}
	while(i<=mid) {
		c[k]=a[i];
		k++;
		i++;
	}
	while(j<=high) {
		c[k]=a[j];
		k++;
		j++;
	}
	for(i=low;i<k;i++) {
		a[i]=c[i];
	}
}

void main(int argc, char *argv[])
{
	int i,j,count;
	int o[MAX];
	char x[10];

    tran = 0.0;
    count = 0;
    printf("--------------------------\n");
    printf("------ UNSORTED ----------\n");
    printf("--------------------------\n");
    while (scanf("%s\n",x) != EOF) {
       o[count] = atoi(x);
/*
       printf ("UNSORTED o[%d]=%d\n",count, o[count]);
*/
       count ++;
	}
    printf("\n--------------------------\n");
    printf("-------- SORTED ----------\n");
    printf("--------------------------\n");

    mergesort(o,0,count-1);
/*
	for (i=0; i<count; i++) {
	   printf("SORTED o[%d]=%d\n",i, o[i]);
	}
*/
    printf ("tran=%15.1f\n", tran);
}