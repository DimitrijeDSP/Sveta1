#include <stdio.h>

int sig2par(int x)
{
	if (x == 0) return (-1);
     if (x < 0)
         return (-2*x-1);
     if (x > 0)
         return (2*x);
     return (-1);
}

int par2sig(int x)
{
	 if (x <= 0) return (-1);
     if (x%2 == 0)
         return (x/2);
     if (x%2 == 1)
         return (-1*(x+1)/2);
     return (-1);
}

main()
{
     unsigned char trt;
     int x1 = 3456, x2=-5555, y1, y2, z1, z2;

     y1 = sig2par(x1);
     y2 = sig2par(x2);
     z1 = par2sig(y1);
     z2 = par2sig(y2);

     printf("%d %d %d\n", x1, y1, z1);
     printf("%d %d %d\n", x2, y2, z2);

     printf("sizeof(short)=%d\n", sizeof(short));
     printf("sizeof(int)=%d\n", sizeof(int));
     printf("sizeof(long)=%d\n", sizeof(long));
     printf("sizeof(char)=%d\n", sizeof(char));

     trt = 255;
     printf("trt=%d\n", trt);
}

