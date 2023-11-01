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
    for (i=0; i<nn; i++) {
		g->v[i] = NULL;
		g->uf_parent[i] = i+1;
		g->uf_size[i] = 1;
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

read_tree(graph *g, node *root)
{
	int i, j, i1, i2, ix, cnt, ones;
	node *r, *t;
	char line[MAXLINE];
	char delims[] = " \n";

    if (fgets(line,MAXLINE,stdin) == NULL) return;
    i1 = atoi((char *) strtok( line, delims ));
    i2 = atoi((char *) strtok( NULL, delims ));

    init_graph(g, i1);

    r = root;
    r->l = NULL; r->r = NULL; r->p = NULL; r->leaf = -1;

    cnt = 0;
    while (fgets(line,MAXLINE,stdin) != NULL) {
	    ix = atoi((char *) strtok( line, delims ));
		j = 0;
		r = root;
		ones = 0;
        for (i=0; i<i2; i++) {
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
		g->v[cnt++] = t;
	}
}

print_graph(graph *g)
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
        printf("\n");
    }
}


kruskal(graph *g, edgearr *ea, int minc)
{
	int i;
    int nclus = g->n;
    int position = 0;
    int maxdist =0;
	for (i=0; i<(g->m)*2; i++) {
 		if (find1(g, ea->e[i]->vid1) != find1(g, ea->e[i]->vid2)) {
			if (nclus == minc) {
				printf("====== THIS CREATES %d CLUSTERS !!! ======= BREAK ==========================\n", minc-1);
			    printf("edge (%d,%d) weight %d \n", ea->e[i]->vid1, ea->e[i]->vid2, ea->e[i]->weight);
                maxdist = ea->e[i]->weight;
				printf("====== THIS CREATES %d CLUSTERS !!! ======= BREAK ==========================\n", minc-1);
 			    position = i;
				break;
			}
			printf("edge (%d,%d) weight %d in MST\n", ea->e[i]->vid1, ea->e[i]->vid2, ea->e[i]->weight);
			union2(g, ea->e[i]->vid1, ea->e[i]->vid2);
			nclus--;
			printf("nclus=%d\n",nclus);
			if (nclus == minc) printf("====== %d CLUSTERS !!! =================================\n", minc);
	    }
	    else
	    	printf("---- SKIP edge (%d,%d) weight %d\n", ea->e[i]->vid1, ea->e[i]->vid2, ea->e[i]->weight);

    }
    printf("=======================================\n");
	i=position+1;
	printf("edge (%d,%d) weight %d\n", ea->e[i]->vid1, ea->e[i]->vid2, ea->e[i]->weight);
    printf("=======================================\n");
	printf("MAXIMUM DISTANCE BETWEEN %d CLUSTERS IS %d", minc ,maxdist);
}

graph_to_array(graph *g, edgearr *ea, int maxdist)
{
	node *x1, *x2;
	int i, j, k, hdist, delta;

    ea->e = malloc(sizeof(edge *)*(g->n));   /* APPROXIMATION !!!! */

    k = 0;
    for (i=0; i<g->n; i++) {
        x1 = g->v[i];
        if (i % 1000 == 0) printf("i=%d\n", i);
        for (j=0; j<g->n; j++) {
			if (i == j) continue;
            x2 = g->v[j];
            if (x1 == NULL || x2 == NULL) continue;
            delta = x1->leaf - x2->leaf;
            if (delta < 0) delta = -1 * delta;
            if (delta >= maxdist) continue;
            hdist = hamming_distance(x1,x2);
            if (hdist < maxdist) {
                ea->e[k] = malloc(sizeof(edge));
                ea->e[k]->vid1 = i+1;
                ea->e[k]->vid2 = j+1;
                ea->e[k]->weight = hdist;
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
    int maxdist = 3;
    int debug = FALSE;
    int dist;

	read_tree(&g, &root);
	if (debug == TRUE) print_graph(&g);
/*
    dist = hamming_distance(g.v[0], g.v[2]);
    print_path(g.v[0]);
    printf("\n");
    print_path(g.v[2]);
    printf("\n");
    printf("dist=%d\n", dist);
*/
	graph_to_array(&g, &e, maxdist);
	print_array(&e);
	sort_array(&e);
	if (debug == TRUE) print_array(&e);
	kruskal(&g, &e, -1);

}

