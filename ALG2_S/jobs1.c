#include <stdio.h>

#define MAXINT 100000
#define DEBUG 0

main(int argc, char*argv[])
{
     int jobs[1000];
     int mach[] = {0,0};
     int val, i, j, jmin, sum;
     int maxm, maxj=argc-2;

     maxm = atoi(argv[1]);

     sum = 0;
	 printf("jobs[%d] = {", maxj);
     for (i=0; i<maxj; i++) {
		 jobs[i] = atoi(argv[i+2]);
		 sum = sum + jobs[i];
		 printf("%d, ", jobs[i]);
	 }
	 printf("}\n");

     for (i=0; i<maxj; i++) {
		 if (DEBUG) printf ("---------- jobs[%d]=%d --------\n", i, jobs[i]);
         jmin = 0;
         val = MAXINT;
         for (j=0; j<maxm; j++) {
			 if (DEBUG) printf("mach[%d]=%d\n", j,mach[j]);
             if (mach[j] < val) {
                 jmin = j;
                 val = mach[j];
             }
		 }
         mach[jmin] = mach[jmin] + jobs[i];
         if (DEBUG) printf("add jobs[%d]=%d to mach[%d]\n", i, jobs[i], jmin);
	 }
     val = 0;
     printf("-------------\n");
	 printf("mach[%d] = {", maxm);
     for (j=0; j<maxm; j++) {
		 printf("%d, ", mach[j]);
         if (mach[j] > val) {
             val = mach[j];
         }
     }
	 printf("}\n");
     printf("-------------\n");
     printf("makespan=%d\n", val);
     printf("ratio %d/%d=%f\n", val,sum/maxm,(float)val/((float)(sum/maxm)));
}
