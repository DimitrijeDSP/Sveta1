#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXINT INT_MAX
#define TRUE 1
#define FALSE 0

#define MAXNODE 1000

typedef struct {
     struct node *l;
     struct node *r;
     struct node *p;
     int leaf;
} node;

typedef struct {
	node **v;
    int n;
    int m;
    int *uf_parent;
    int *uf_size;
    unsigned int *x;
} graph;

typedef struct {
     int vid1;
     int vid2;
     int weight;
} edge;

typedef struct {
	edge **e;
	int m;
} edgearr;

typedef int (*compfn)(const void*, const void*);


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

int valh(int x)
{
	return (x % PRIME);
}

#define DEBUG FALSE

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

int compare_edge(edge **i, edge **j)
{
/*	printf("compare_diff: %d %d\n", (*i)->wtdiff, (*j)->wtdiff);  */
	if ((*i)->weight > (*j)->weight) return(1);
	if ((*i)->weight < (*j)->weight) return(-1);
    return(0);
}

sort_array(edgearr *ea)
{
    qsort((void *)ea->e,ea->m,sizeof(edge *), (compfn)compare_edge);
}

print_array(edgearr *ea)
{
	int i;

    printf("======================================\n");
    printf(" m=%d\n", ea->m);
    printf("======================================\n");
	for (i=0; i<ea->m; i++) {
	   if (ea->e[i] == NULL) continue;
	   printf("%d %d %d\n", ea->e[i]->vid1, ea->e[i]->vid2, ea->e[i]->weight);
    }
}

init_graph(graph *g, int nn)
{
	int i;
	g->n=nn;
	g->m=0;
    g->v = malloc(sizeof(node *)*(g->n));
    g->uf_parent = malloc(sizeof(int)*(g->n));
    g->uf_size = malloc(sizeof(int)*(g->n));
    g->x = malloc(sizeof(unsigned int)*(g->n));
    for (i=0; i<nn; i++) {
		g->v[i] = NULL;
		g->uf_parent[i] = i+1;
		g->uf_size[i] = 1;
		g->x[i] = (unsigned int) 0x0;
	}
}


int find1(graph *g, int x)
{
	if (g->uf_parent[x-1] == x)
	    return (x);
	else
	    return( find1(g, g->uf_parent[x-1]) );
}

union2(graph *g, int x1, int x2)
{
	 int x11, x22;

	 x11 = find1 (g, x1);
	 x22 = find1 (g, x2);

	 if (x11 == x22) return;

	 if (g->uf_size[x11-1] >= g->uf_size[x22-1]) {
		 g->uf_size[x11-1] = g->uf_size[x11-1] + g->uf_size[x22-1];
		 g->uf_parent[x22-1] = x11;
	 }
	 else {
	     g->uf_size[x22-1] = g->uf_size[x11-1] + g->uf_size[x22-1];
		 g->uf_parent[x11-1] = x22;
	 }
}

print_path_recurse(node *x)
{
	  node *y;
	  int bit;
      y = (node *) x->p;
      if (y != NULL) {
		  print_path((node *)y);
          if (y->l != NULL && y->l == (struct node *)x) bit = 0;
          if (y->r != NULL && y->r == (struct node *)x) bit = 1;
          printf("%d ", bit);
      }
}

#define DEPTH 100
print_path(node *x)
{
    int i, d, stack[DEPTH];
    d = find_path(x, stack, DEPTH);
    for (i=d-1; i>=0; i--) {
        printf("%d ", stack[i]);
	}
	printf("\n");
}

int find_path(node *x, int *st, int maxd)
{
	  node *y, *z;
	  int bit, sp;

	  sp = 0;
	  z = (node *) x;
      y = (node *) z->p;
	  while (y != NULL) {
          bit = 2;
          if (y->l != NULL && y->l == (struct node *)z) bit = 0;
          if (y->r != NULL && y->r == (struct node *)z) bit = 1;
          if (sp < maxd) st[sp++] = bit;
          z = y;
          y = (node *) z->p;
      }
      return(sp);
}

int find_node(graph *g, node *root, unsigned int x)
{
   int i, ix;
   int n = 24;
   int array[24];
   node *p;

   for (i=0; i<n; i++) {
       array[n-1-i] = (x >> i) & 1;
   }

   p = root;
   for (i=0; i<n; i++) {
       if (array[i] == 1) p = (node *)p->r;
       if (array[i] == 0) p = (node *)p->l;
   }
   ix = -1;
   for (i=0; i<g->n; i++) {
	   if (g->v[i] == p) {
		   ix = i+1;
		   break;
	   }
   }
   return (ix);
}

int hamming_distance(node *x1, node *x2)
{
	  node *y1, *z1, *y2, *z2;
	  int bit1, bit2, hdist;

      hdist = 0;
	  z1 = (node *) x1;
      y1 = (node *) z1->p;
	  z2 = (node *) x2;
      y2 = (node *) z2->p;
	  while (y1 != NULL && y2 != NULL) {
          bit1 = 2;
          if (y1->l != NULL && y1->l == (struct node *)z1) bit1 = 0;
          if (y1->r != NULL && y1->r == (struct node *)z1) bit1 = 1;
          if (y2->l != NULL && y2->l == (struct node *)z2) bit2 = 0;
          if (y2->r != NULL && y2->r == (struct node *)z2) bit2 = 1;
          if (bit1 != bit2) hdist++;
          z1 = y1;
          y1 = (node *) z1->p;
          z2 = y2;
          y2 = (node *) z2->p;
      }
      return (hdist);
}

int hamming_distance_recurse(node *x1, node *x2)
{
	  node *y1, *y2;
	  int bit1, bit2, hd1, hd2;
      y1 = (node *) x1->p;
      y2 = (node *) x2->p;
      hd2 = 0;
      bit1 = -1;
      bit2 = -1;
      if (y1 == NULL && y2 == NULL) { printf("root\n"); hd1 = 0; hd2 = 0;}
      if (y1 != NULL && y2 != NULL) {
		  hd1 = hamming_distance((node *)y1, (node *)y2);
          printf("hd1=%d\n", hd1);
          if (y1->l != NULL && y1->l == (struct node *)x1) bit1 = 0;
          if (y1->r != NULL && y1->r == (struct node *)x1) bit1 = 1;
          if (y2->l != NULL && y2->l == (struct node *)x2) bit2 = 0;
          if (y2->r != NULL && y2->r == (struct node *)x2) bit2 = 1;
          hd2 = 0;
          if (bit1 < 0 || bit2 < 0) printf("ERROR!!!!\n");
          if (bit1 != bit2) hd2 = 1;
          printf("hd2=%d\n", hd2);
      }
      return (hd1 + hd2);
}

#define MAXLINE 100

read_tree(graph *g, node *root, hasht *ht)
{
	int i, j, i1, i2, ix, cnt, ones;
	node *r, *t;
	char line[MAXLINE];
	char delims[] = " \n";
	unsigned int xbit;

    if (fgets(line,MAXLINE,stdin) == NULL) return;
    i1 = atoi((char *) strtok( line, delims ));
    i2 = atoi((char *) strtok( NULL, delims ));

    init_graph(g, i1);

    r = root;
    r->l = NULL; r->r = NULL; r->p = NULL; r->leaf = -1;

    cnt = 0;
    while (fgets(line,MAXLINE,stdin) != NULL) {
		xbit = (unsigned int ) 0x0;
	    ix = atoi((char *) strtok( line, delims ));
		j = 0;
		r = root;
		ones = 0;
        for (i=0; i<i2; i++) {
            xbit |= ((ix == 1) << i2-i-1);
			if (ix == 0) t = (node *) r->l;
			if (ix == 1) t = (node *) r->r;
			if (ix == 1) ones++;
		    if (t == NULL) {
			    t = malloc (sizeof(node));
                t->l = NULL; t->r = NULL; t->p = (struct node *) r; t->leaf = 0;
			    if (ix == 0) r->l = (struct node *) t;
			    if (ix == 1) r->r = (struct node *) t;
		    }
			r = t;
			j = j+2;
	        ix = atoi((char *) strtok( NULL, delims ));
	    }
		t->leaf = ones;
		g->v[cnt] = t;
		if (testh(ht, xbit) != TRUE) puth(ht,xbit);
		g->x[cnt] = xbit;
		cnt++;
	}
}

print_graph(graph *g, hasht *ht)
{
	node *p;
	int i;

    printf("======================================\n");
    printf(" n=%d \n", g->n);
    printf("======================================\n");
    for (i=0; i<g->n; i++) {
        p = g->v[i];
        if (p == NULL) continue;
        printf("%d: ", i+1);
		print_path(p);
		if (testh(ht, g->x[i]) != TRUE) printf("%d NOT FOUND IN HASH \n", g->x[i]);
        printf("\n");
    }
}


kruskal(graph *g, edgearr *ea, int minc)
{
	int i;
    int nclus = g->n;
	for (i=0; i<ea->m; i++) {
 		if (find1(g, ea->e[i]->vid1) != find1(g, ea->e[i]->vid2)) {
			union2(g, ea->e[i]->vid1, ea->e[i]->vid2);
			nclus--;
	    }
    }
    printf("=======================================\n");
	printf("nclus = %d\n", nclus);
    printf("=======================================\n");
}

int mask_2bit(int n, unsigned int *mask, int mode)
{
    int i, j, k, y, xx, *x, cnt, nobits;
    unsigned int bbb;

    x = (int *) malloc(sizeof(int)*n);

    for (k=0; k<n; k++) {
        x[k] = 0;
	}

    cnt = 0;
    for (i=0; i<n; i++) {
        for (j=0; j<=i; j++) {
            nobits=0;
	        bbb = 0;
            if (x[i] == 0) y = 1;
            if (x[i] == 1) y = 0;
            if (x[j] == 0) y = 1;
            if (x[j] == 1) y = 0;
            for (k=0; k<n; k++) {
  	            if (k == i || k == j)
                    xx = y;
                else
                    xx = x[k];
                if (xx == 1) nobits++;
                bbb |= ((xx == 1) << n-k-1);
            }
            if (mode == 0)
                mask[cnt++] = bbb;
            else
                mask[cnt++] = nobits;
        }
    }
    return (cnt);
}

graph_to_array(graph *g, node *root, edgearr *ea, hasht *ht)
{
	node *x1, *x2, *p, *q;
	int i, j, k, delta, cnt, i1, i2;
    unsigned int mask[400], t;
    int hdist[400];
    int n = 24;

    cnt = mask_2bit(24, mask,0);
    cnt = mask_2bit(24, hdist,1);

    ea->e = malloc(sizeof(edge *)*(g->n)*10);   /* APPROXIMATION !!!! */

    k = 0;

    for (i=0; i<g->n; i++) {
        if (i % 10000 == 0) printf("i=%d\n", i);
        p = g->v[i];
        for (j=0; j<g->n; j++) {
			if (i == j) continue;
            q = g->v[j];
            if (p == q) {
                ea->e[k] = malloc(sizeof(edge));
                ea->e[k]->vid1 = i+1;
                ea->e[k]->vid2 = j+1;
                ea->e[k]->weight = 0;
		        k++;
			}
		}
	}

    for (i=0; i<g->n; i++) {
        p = g->v[i];
        if (i % 10000 == 0) printf("i=%d\n", i);
        if (p == NULL) continue;
        for (j=0; j<cnt; j++) {
			t = (g->x[i])^(mask[j]);
		    if (testh(ht, t) == TRUE) {
				i1 = i+1;
				i2 = find_node(g, root, t);
                ea->e[k] = malloc(sizeof(edge));
                ea->e[k]->vid1 = i1;
                ea->e[k]->vid2 = i2;
                ea->e[k]->weight = hdist[j];
		        k++;
			}
	    }
    }

    ea->m = k;
}

main(int argc, char *argv[])
{
	graph g;
	node root;
	edgearr e;
    hasht ht;

    int maxdist = 3;
    int debug = FALSE;
    int dist, stat;

    stat = inith(&ht);

    printf("read_tree START\n");
	read_tree(&g, &root, &ht);
    printf("read_tree END\n");
	if (debug == TRUE) printh(&ht, 0, 100);
    if (debug == TRUE) print_graph(&g,&ht);

    printf("graph_to_array START\n");
	graph_to_array(&g, &root, &e, &ht);
    printf("graph_to_array END\n");
    printf("sort_array START\n");
	sort_array(&e);
    printf("sort_array END\n");
	print_array(&e);
    printf("kruskal START\n");
	kruskal(&g, &e, -1);
    printf("\nkruskal END\n");
}

