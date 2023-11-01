#include <stdio.h>
#include <stdlib.h>
#include <math.h>

main()
{
   float x1, y1, x2, y2;

   x1=26433.3333; y1=13433.3333;
   x2=27153.6111; y2=13203.3333;
   printf("W[23][18]=756.108093\n");
   printf("dist=%f\n", sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))); 
}