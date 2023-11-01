#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


int *getset(int LEN, unsigned long x)
{
	int i,k;
	unsigned long mask, masked_x, thebit;
    int *buffer = malloc(sizeof(int) * (LEN+1));

    for(k=0; k<LEN; k++) buffer[k] = -1;

    i=0;
    for(k=0; k<LEN; k++){
       mask =  1 << k;
       masked_x = x & mask;
       thebit = masked_x >> k;
       if (thebit == 1) {
          buffer[i] = k;
          i++;
	  }
    }
    buffer[i] = -1;

    return buffer;
}

printset(int LEN, unsigned long x)
{
	int i,k;
	unsigned long mask, masked_x, thebit;
    int *buffer;

    buffer = getset(LEN,x);
    for(k=0; k<LEN; k++) {
		if (buffer[k] == -1) break;
    }

    printf("{");
    for (i=LEN-1; i>=0; i--) {
		if(buffer[i] == -1) continue;
		printf("%d, ",buffer[i]+2);
	}
    printf("} = %d\n", getindex(LEN,x));
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

main (int argc, char *argv[])
{
	int i, stat;
	long unsigned int x, xx, xmax;
	int n = atoi(argv[1]);

    xmax = ~(~0 << n);
    for (xx=1; xx<xmax; xx =  (xx << 1) | 1) {
		x = xx;
		printf("============ %d ==============\n", x);
	    for (i=0; i<nck(n,bitcount(x)); i++) {
			printf("%3d ",i);
            printbin(n, x);
            printset(n, x);
            printset(n, ~x);
            stat = next_combination(&x);
            if (stat == 0) {
			    printf("error\n");
			    break;
	        }
		}
    }
}
