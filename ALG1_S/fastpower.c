#include <stdio.h>
#include <stdlib.h>

int count;

fastpower(long a, long b)
{
	 long c,ans;

     if (b == 1)
        return a;
     else {
		count++;
        c = a*a;
        count++;
        ans = fastpower(c,b/2);
        if (b%2 == 1) {
			return a*ans;
	    }
        else
           return ans;
     }
}

main (int argc, char *argv[])
{
	long x,y,z;

    count = 0;
	x = atoi(argv[1]);
	y = atoi(argv[2]);
	z = fastpower(x,y);
    printf("power(%d,%d)=%d count=%d\n",x,y,z,count);
}