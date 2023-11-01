#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define INF 21474800

#define TRUE 1
#define FALSE 0

#define MIN(a,b) (((a)<(b))?(a):(b))

unsigned nck(unsigned n, unsigned k)  /* n choose k */
{
    int i;
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    int result = n;
    for( i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

int next_combination(unsigned long *x)
{
  unsigned long u = (*x) & -(*x);
  unsigned long v = u + (*x);
  if (v==0)
    return 0;
  (*x) = v +(((v^(*x))/u)>>2);
  return 1;
}

printbin(int LEN, unsigned long x)
{
	int i, s;
	char buffer [LEN+2];

    itoa (x,buffer,2);
    s = strlen(buffer);
    if (s>LEN) s=LEN;
    for (i=0;i<LEN-s;i++)
         printf ("%c", '0');
    printf("%s %d ",buffer, x);
}

int *get_bits(int n, int bitswanted){
  int *bits = malloc(sizeof(int) * bitswanted);

  int k;
  for(k=0; k<bitswanted; k++){
    int mask =  1 << k;
    int masked_n = n & mask;
    int thebit = masked_n >> k;
    bits[k] = thebit;
  }

  return bits;
}


int getindex(int LEN, unsigned long x)
{
	int i,k, sum;
	unsigned long mask, masked_x, thebit;

    sum = 0;
    i=1;
    for(k=0; k<LEN; k++){
       mask =  1 << k;
       masked_x = x & mask;
       thebit = masked_x >> k;
       if (thebit == 1) {
          sum = sum + nck(k,i);
          i++;
	  }
    }

    return sum;
}


getset(int *buffer, int LEN, unsigned long x)
{
	int i,k;
	unsigned long mask, masked_x, thebit;

    for(k=0; k<LEN; k++) buffer[k] = -1;

    i=0;
    for(k=0; k<LEN; k++){
       mask =  1 << k;
       masked_x = x & mask;
       thebit = masked_x >> k;
       if (thebit == 1) {
          buffer[i] = k+2;
          i++;
	  }
    }
    buffer[i] = -1;
}

printset(int LEN, unsigned long x)
{
	int i,k;
	unsigned long mask, masked_x, thebit;
    int *buffer = malloc (sizeof(int)*(LEN+1));

    getset(buffer, LEN,x);
    for(k=0; k<LEN; k++) {
		if (buffer[k] == -1) break;
    }

    printf("{");
    for (i=LEN-1; i>=0; i--) {
		if(buffer[i] == -1) continue;
		printf("%d, ",buffer[i]);
	}
    printf("}");
}

int bitcount(unsigned int x)
{
   int bc = 0;
   while(x > 0) {
	  if ( x & 1 == 1 )
		 bc++;
	  x >>= 1;
  }
  return bc;
}


main(int argc, char *argv[])
{
	int i, stat;
	long unsigned int x, xx, xmax, xold;

	int W[5][5] = { {0,  0,  0,  0,  0},
		            {0,  0,  2,  9,INF},
	                {0,  1,  0,  6,  4},
	                {0,INF,  7,  0,  8},
	                {0,  6,  3,INF,  0}};
    int icard;   /* current cardinality */
    int *i1, i1ind;     /* list of elements in given set     */
    int *i2, i2ind;     /* list of elements NOT in given set */
	int nelem = 4, ncomb, minval, curval;
	int n = nelem - 1;
	int card[nelem]; /* for every set cardinality we keep start index :-) */
	int *D;
	int A[nelem][10000];

    xx = 0;
    icard=0;
    card[icard] = 0;
    ncomb = n;
    D = malloc(sizeof(int)*ncomb);
    i1 = (int *)malloc(sizeof(int) * (nelem+1));
    i2 = (int *)malloc(sizeof(int) * (nelem+1));
    printf("######################################### %d  ##############################################\n", xx);
	for (i = 2; i<=nelem; i++) {
		D[i] = W[i][1];
		A[i][0] = W[i][1];
		printf("A[%d][%d] = W[%d][%d] = %d\n", i, 0, i, 1, W[i][1]);
	}

    xmax = ~(~0 << n);
    icard=1;
    for (xx=1; xx<xmax; xx =  (xx << 1) | 1) {
        printf("######################################### %d  ##############################################\n", xx);
		x = xx;
		card[icard]=card[icard-1]+ncomb;
		ncomb = nck(n,bitcount(x));
		printf("ncomb=%d\n", ncomb);
		D = realloc(D, card[icard]+ncomb); /* make room for new values */
		icard++;
	    for (i=0; i<ncomb; i++) {
            getset(i1, n,~x);
            getset(i2, n, x);
            i1ind = 0;
            while (i1[i1ind] != -1) {
				printf("------------- i1[%d]=%d\n", i1ind, i1[i1ind]);
				i2ind = 0;
				minval = INF;
				while (i2[i2ind] != -1) {
					printbin(n,x);
					xold = x^(1<<(i2[i2ind]-2));
					printbin(n,xold);
					printf("W[%d][%d] + A[%d][%d] = %d + %d\n", i1[i1ind], i2[i2ind], i2[i2ind], xold, W[i1[i1ind]][i2[i2ind]], A[i2[i2ind]][xold]);
					curval = W[i1[i1ind]][i2[i2ind]] + A[i2[i2ind]][xold];
					if(curval < minval) minval = curval;
				    printf("...... i2[%d]=%d\n", i2ind, i2[i2ind]);
					i2ind++;
				}
				A[i1[i1ind]][x] = minval;
				printf("==================================> A[%d][%d]=%d\n", i1[i1ind], x, minval);
				i1ind++;
			}

            stat = next_combination(&x);
            if (stat == 0) {
			    printf("error\n");
			    break;
	        }
		}
    }

    x=7;
    printf("######################################### %d  ##############################################\n", x);
    getset(i2, n+1, x);
    i2ind = 0;
    minval = INF;
	while (i2[i2ind] != -1) {
		printbin(n,x);
	    xold = x^(1<<(i2[i2ind]-2));
		printbin(n,xold);
		printf("W[%d][%d] + A[%d][%d] = %d + %d\n", 1, i2[i2ind], i2[i2ind], xold, W[i1[i1ind]][i2[i2ind]], A[i2[i2ind]][xold]);
		curval = W[1][i2[i2ind]] + A[i2[i2ind]][xold];
		if(curval < minval) minval = curval;
		printf("...... i2[%d]=%d\n", i2ind, i2[i2ind]);
		i2ind++;
	}
	A[1][x] = minval;
	printf("==================================> A[%d][%d]=%d\n", 1, x, minval);

}