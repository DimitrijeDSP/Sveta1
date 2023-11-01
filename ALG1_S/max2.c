#include <stdio.h>

#define MAX 100001

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
		comp++;
		if(a[i]<a[j]) {
			c[k]=a[i];
			k++;
			i++;
		}
		else {
			c[k]=a[j];
			k++;
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

    comp = 0;
    count = 0;
    printf("--------------------------\n");
    printf("------ UNSORTED ----------\n");
    printf("--------------------------\n");
    while (scanf("%s\n",x) != EOF) {
       o[count] = atoi(x);
       count ++;
	}
    printf("\n--------------------------\n");
    printf("-------- SORTED ----------\n");
    printf("--------------------------\n");

    mergesort(o,0,count-1);
    printf("second max = %d\n",o[count-2]);
    printf ("n=%d comp=%d shold be %d\n", count, comp, count+log2x(count)-2);
    printf("log2x(%d)=%d\n", count,log2x(count));
}