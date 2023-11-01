#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAXINT INT_MAX
#define DEBUG FALSE

#define PRIME 500041

typedef struct {
	int v;
	struct buc *next;
} buc;

typedef struct {
    buc **bucket;
    int size;
} hasht;

int inith(hasht *ht)
{
   int i;

   ht->bucket = malloc(PRIME*sizeof(struct buc *));
   if (ht->bucket == NULL) {
	   printf("malloc error, exit");
	   return (-1);
   }
   for (i=0; i<PRIME; i++)
       ht->bucket[i] = NULL;
   return (0);
}


int testh(hasht *ht, int x)
{
   buc *b;
   int hash, stat;

   stat = FALSE;
   hash = valh(x);
   b = ht->bucket[hash];
   while (b != NULL) {
	  if (b->v == x) {
		  stat = TRUE;
		  break;
      }
      b = (buc *) b->next;
   }
   return stat;
}

readh(hasht *ht, char *file)
{
   FILE *in;
   int count, hash, x;

   in = fopen(file, "r");
   count=0;
   while (fscanf(in,"%d",&x) != EOF) {
          if (testh(ht, x) == TRUE) continue;
          puth(ht,x);
          count ++;
   }
   fclose(in);
}

checkh(hasht *ht, char *file)
{
   FILE *in;
   int count, hash, x;

   in = fopen(file, "r");
   count=0;
   while (fscanf(in,"%d",&x) != EOF) {
       if (testh(ht, x) == FALSE) printf("CHECK HASH %d not found\n", x);
   }
   fclose(in);
}

int valh(int x)
{
	return (x % PRIME);
}

puth(hasht *ht, int x)
{
   buc *bold;
   buc *b;
   int i, y;

   y = valh(x);

   if (DEBUG == TRUE) printf("puth x=%d y=%d\n",x, y);
   bold = ht->bucket[y];
   b = (buc *) malloc (sizeof(buc));
   ht->bucket[y] = b;
   b->next = (struct buc *) bold;
   b->v = x;
}

printh(hasht *ht, int start, int stop)
{
   buc *b;
   int i;

   for (i=start; i<stop; i++) {
       b = ht->bucket[i];
       printf ("hash[%d] = [", i);
       while (b != NULL) {
		   printf ("%d, ",b->v);
		   b = (buc *) b->next;
	   }
       printf("]\n");
   }
}


stath(hasht *ht)
{
   buc *b;
   int i,j,k,max;

   j = 0;
   max = 0;
   for (i=0; i<PRIME; i++) {
	   k = 0;
       b = ht->bucket[i];
       if (b != NULL) j++;
       while (b != NULL) {
		   k++;
		   b = (buc *) b->next;
	   }
	   if (k > max) max = k;
   }
   printf("filled buckets %d out of %d , max chain %d\n", j, PRIME, max);
}

int x2sum(hasht *ht, int start, int stop)
{
   buc *b;
   int i;
   int t,x,y;
   int *tv, nt, count;

   nt = stop - start + 1;
   tv = (int *) malloc(nt * sizeof(int));

   count = 0;
   for (i=0; i<nt; i++) {
	   tv[i] = 0;
       t = start+i;
       for (x=1; x<t; x++) {
           if (testh(ht,x) == FALSE) continue;
           y = t-x;
           if (testh(ht,y) == FALSE) continue;
           if (x == y) continue;
           printf("  %d + %d = %d\n", x,y,t);
           tv[i]++;
	   }
       printf(" ####################### tv[%d]=%d\n", t, tv[i]);
       if (tv[i] > 0) count ++;
   }
   return count;
}

main(int argc, char *argv[])
{
   hasht ht;
   int stat, cnt, t1, t2;

   printf("INITH\n");
   stat = inith(&ht);
   printf("READH\n");
   readh(&ht, argv[1]);
   printf("CHECKH\n");
   readh(&ht, argv[1]);
   printf("PRINTH\n");
   printh(&ht, 0, 10);
   printf("STATH\n");
   stath(&ht);
   t1 = 2500;
   t2 = 4000;
   cnt = x2sum(&ht, t1,t2);
   printf("2sum range t [%d,%d] count=%d\n", t1, t2, cnt);
}

