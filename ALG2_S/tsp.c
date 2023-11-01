/* TSP according to Tim. R. lesson  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define INF HUGE_VALF

#define TRUE 1
#define FALSE 0

#define MIN(a,b) (((a)<(b))?(a):(b))

#define DEBUG FALSE

typedef struct {
	float x;
	float y;
} point;

#define MAXP 100

typedef struct {
	point p[MAXP];
	int np;
} map;


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
    int *buffer = (int *) malloc(sizeof(int)*(LEN+2));

    getset(buffer,LEN,x);
    for(k=0; k<LEN; k++) {
		if (buffer[k] == -1) break;
    }

    printf("{");
    for (i=LEN-1; i>=0; i--) {
		if(buffer[i] == -1) continue;
		printf("%d, ",buffer[i]);
	}
    printf("}");
    free(buffer);
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

readmap(map *m)
{
	int i;
	float t1, t2;

   FILE * fp;

   fp = fopen ("tsp.txt", "r");

	fscanf(fp, "%d",&i);
	m->np = i;
	for (i=0; i<m->np; i++)
	{
		fscanf(fp, "%f %f", &t1, &t2);
		m->p[i].x = t1;
		m->p[i].y = t2;
	}
	fclose(fp);
}

printmap(map *m)
{
	int i;

	printf("no points = %d\n", m->np);
	for (i=0; i<m->np; i++)
	{
		printf("x[%d]=%f y[%d]=%f\n", i, m->p[i].x, i, m->p[i].y);
	}
}

float getval(float *a, int LEN, int maxc, int i, int j)
{
	float v;
    int ix;


	ix = getindex(LEN, j);

	v = a[maxc*(i-2)+ix];
	/*
	if (v <= 0.0 || ix < 0)
	     printf("GETVAL LEN=%d i=%d j=%d v=%f ix=%d\n", LEN,i,j,v,ix);
    */
	return 	v;
}

setval(float *a, int LEN, int maxc, int i, int j, float v)
{
	int ix;

	/* GETVAL LEN=24 i=3 j=4 v=0.000000 ix=2 */

	ix = getindex(LEN, j);
	a[maxc*(i-2)+ix] = v;
	/*
	if (a[maxc*(i-2)+ix] <= 0.0 || v <= 0.0 || ix < 0)
	     printf("SETVAL LEN=%d i=%d j=%d v=%f ix=%d\n", LEN,i,j,v,ix);
    */
}

float tsp(map *m)
{
    long unsigned int x, xx, xmax, xold;
	int nelem = m->np;
    int i,j, stat, dim;
    int icard;   /* current cardinality */
    int *i1, i1ind;     /* list of elements in given set     */
    int *i2, i2ind;     /* list of elements NOT in given set */
	int ncomb, nbit, maxcomb;
	float minval, curval;
	int n = nelem - 1;
	float W[nelem+1][nelem+1], xd, yd;
	float *AC, *AP, *AT;  /* current, previous, temp */

    printf("%%%%% MEMORY REQUIREMENS %%%%%\n");
    maxcomb = 0;
    for (i=1; i<=n; i++) {
		j = nck(n, i);
		if (j > maxcomb) maxcomb = j;
        printf("%dC%d=%d --- %d * %d = %d\n", n, i, j, i, j, i*j);
    }
    printf("%%%%% MEMORY REQUIREMENS %%%%%\n");

    dim = ~(~0 << nelem);
    printf("dim = %d\n", dim);

    i1 = (int *) malloc(sizeof(int) * (nelem+1));
    i2 = (int *) malloc(sizeof(int) * (nelem+1));
/*
    AC = (float *) malloc(sizeof(float)*(n/2)*nck(n,n/2));
    AP = (float *) malloc(sizeof(float)*(n/2)*nck(n,n/2));
*/
    AC = (float *) malloc(sizeof(float)*n*maxcomb);
    AP = (float *) malloc(sizeof(float)*n*maxcomb);

	for (i=1; i<=nelem; i++) {
	    for (j=1; j<=nelem; j++) {
			 if (i == j) {
				 W[i][j] = 0.0;
				 W[j][i] = 0.0;
			 }
		     else {
			     xd = m->p[i-1].x - m->p[j-1].x;
			     yd = m->p[i-1].y - m->p[j-1].y;
		         W[i][j] = sqrt(xd*xd + yd*yd);
		         W[j][i] = W[i][j];
			 }
		}
	}

    printf("$$$$$$$$$$ MATRIX W $$$$$$$$$$$$$$\n");
	for (i=1; i<=nelem; i++) {
	    for (j=1; j<=nelem; j++) {
			printf("W[%d][%d]=%f\n", i, j, W[i][j]);
		}
	}

    xx = 0;
    ncomb = n;
    printf("######################################### %d  ##############################################\n", xx);
	for (i = 2; i<=nelem; i++) {
		setval(AC, n, maxcomb, i, 0, W[i][1]);   /* A[i][0] = W[i][1];   */
		printf("A[%d][%d] = W[%d][%d] = %f\n", i, 0, i, 1, W[i][1]);
	}

    xmax = ~(~0 << n);
    for (xx=1; xx<xmax; xx =  (xx << 1) | 1) {
        printf("######################################### %d  ##############################################\n", xx);
		AT = AP; AP = AC; AC = AT;
		x = xx;
		nbit = bitcount(x);
		ncomb = nck(n,nbit);
		printf("nbit=%d ncomb=%d\n", nbit, ncomb);
	    for (i=0; i<ncomb; i++) {
            getset(i1, n,~x);
            getset(i2, n, x);
            i1ind = 0;
            while (i1[i1ind] != -1) {
				if (DEBUG == TRUE) printf("------------- i1[%d]=%d\n", i1ind, i1[i1ind]);
				i2ind = 0;
				minval = INF;
				while (i2[i2ind] != -1) {
					if (DEBUG == TRUE) printbin(n,x);
					xold = x^(1<<(i2[i2ind]-2));
					if (DEBUG == TRUE) printbin(n,xold);
					if (DEBUG == TRUE) printf("W[%d][%d] + A[%d][%d] = %f + %f\n", i1[i1ind], i2[i2ind], i2[i2ind], xold, W[i1[i1ind]][i2[i2ind]], getval(AP, n, maxcomb, i2[i2ind], xold));
					/* curval = W[i1[i1ind]][i2[i2ind]] + A[i2[i2ind]][xold];  */
					curval = W[i1[i1ind]][i2[i2ind]] + getval(AP, n, maxcomb, i2[i2ind], xold);
					if(curval < minval) minval = curval;
				    if (DEBUG == TRUE) printf("...... i2[%d]=%d\n", i2ind, i2[i2ind]);
					i2ind++;
				}
				/* A[i1[i1ind]][x] = minval;  */
				setval(AC, n, maxcomb, i1[i1ind], x, minval);
				if (DEBUG == TRUE) printf("==================================> A[%d][%d]=%f\n", i1[i1ind], x, minval);
				i1ind++;
			}

            stat = next_combination(&x);
            if (stat == 0) {
			    printf("error\n");
			    break;
	        }
		}
    }

    x=xmax;
    printf("######################################### %d  ##############################################\n", x);
    getset(i2, n+1, x);
    i2ind = 0;
    minval = INF;
	AT = AP; AP = AC; AC = AT;
	while (i2[i2ind] != -1) {
		printbin(n,x);
	    xold = x^(1<<(i2[i2ind]-2));
		printbin(n,xold);
		printf("W[%d][%d] + A[%d][%d] = %f + %f\n", 1, i2[i2ind], i2[i2ind], xold, W[1][i2[i2ind]], getval(AP, n, maxcomb, i2[i2ind], xold));
		/* curval = W[1][i2[i2ind]] + A[i2[i2ind]][xold];  */
		curval = W[1][i2[i2ind]] + getval(AP, n, maxcomb, i2[i2ind], xold);
		if(curval < minval) minval = curval;
		printf("...... i2[%d]=%d\n", i2ind, i2[i2ind]);
		i2ind++;
	}
	/* A[1][x] = minval;  */
/*    setval(AC, n, maxcomb, 1, x, minval);  */
	printf("==================================> A[%d][%d]=%f\n", 1, x, minval);

	return (minval);
}

main()
{
	float mintour;
	map m;
	readmap(&m);
	printmap(&m);
    mintour = tsp(&m);
    printf("mintour=%f\n", mintour);
}

