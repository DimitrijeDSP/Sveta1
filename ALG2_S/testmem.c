#include <stdio.h>
#include <stdlib.h>

main()
{
     int *a;
     a = malloc (sizeof(int)*100);
     a[50] = 999;
     printf("a[50]=%d\n", a[50]);
     a = realloc (a, sizeof(int)*200);
     a[190] = 888;
     printf("a[50]=%d\n", a[50]);
     printf("a[190]=%d\n", a[190]);
}
