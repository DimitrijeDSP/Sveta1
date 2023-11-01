#include <stdio.h>
#include <math.h>

main()
{
	float x = 10.0, y = HUGE_VALF;
	if (x > y)
      printf("%f\n", x);
	else
      printf("%f\n", y);
}