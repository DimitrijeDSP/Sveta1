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


main(int argc, char *argv[])
{
   hasht ht;
   int stat;

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
}

