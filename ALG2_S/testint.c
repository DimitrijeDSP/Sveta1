#include <stdio.h>
#include <limits.h>

main()
{
   int i;

   for (i=0; i<INT_MAX; i=i+10000)
   {
	   if (i < 0) break;
        printf("%d ", i);
   }
}