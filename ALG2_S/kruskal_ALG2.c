#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXINT INT_MAX
#define TRUE 1
#define FALSE 0

#define MAXNODE 1000

typedef struct {
     int vid;
     int weight;
     struct vertex *next;
} vertex;

typedef struct {
     int vid1;
     int vid2;
     int weight;
} edge;

typedef struct {
	vertex **v;
    int n;
    int m;
    int undir;
    int *uf_parent;
    int *uf_size;
} graph;

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

graph_to_array(graph *g, edgearr *ea, int undirected)
{
	vertex *p;
	int i, i1, j, k;

    k = 1;
    if (undirected == TRUE) k = 2;
    ea->e = malloc(sizeof(edge *)*(g->m)*k);

    j = 0;
    for (i=0; i<g->n; i++) {
        p = g->v[i];
        if (p == NULL) continue;
        i1 = p->vid;
		p = (vertex *) p->next;
	    while (p != NULL) {
            ea->e[j] = malloc(sizeof(edge));
            ea->e[j]->vid1 = i1;
            ea->e[j]->vid2 = p->vid;
            ea->e[j]->weight = p->weight;
		    p = (vertex *) p->next;
		    j++;
        }
    }
    ea->m = j;
}

insert_graph(graph *g, int n1, int n2, int wx)
{
	vertex *p, *q;

    p = g->v[n1-1];
    if (p == NULL) {
        p = (vertex *) malloc(sizeof(vertex));
        p->vid = n1;
        p->next = NULL;
        g->v[n1-1] = p;
        p->weight = 0;
    }
    q = (vertex *) malloc(sizeof(vertex));
    q->vid = n2;
    q->weight = wx;
    q->next = p->next;
    p->next = (struct vertex *) q;
}

init_graph(graph *g, int nn, int uu)
{
	int i;
	g->n=nn;
	g->m=0;
    g->undir = uu;
    g->v = malloc(sizeof(vertex *)*(g->n));
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


read_graph(graph *g, int undirected)
{
	vertex *p, *q;
	int nn, n1, n2, wx;
	g->n=0;
	scanf("%d", &nn);
	init_graph(g,nn, undirected);

	while (scanf("%d %d %d",&n1, &n2, &wx) > 0)
	{
        g->m++;
        insert_graph(g, n1, n2, wx);
        if (undirected == TRUE)
            insert_graph(g, n2, n1, wx);
    }
}

print_graph(graph *g)
{
	vertex *p;
	int i;

    printf("======================================\n");
    printf(" n=%d m=%d u=%d\n", g->n, g->m, g->undir);
    printf("======================================\n");
    for (i=0; i<g->n; i++) {
        p = g->v[i];
        if (p == NULL) continue;
        printf("%d: ", p->vid);
	    while (p->next != NULL) {
		    p = (vertex *) p->next;
            printf("%d[%d] ", p->vid, p->weight);
        }
        printf("\n");
    }
}

kruskal(graph *g, edgearr *ea)
{
	int i;
	for (i=0; i<(g->m)*2; i++) {
 		if (find1(g, ea->e[i]->vid1) != find1(g, ea->e[i]->vid2)) {
			printf("edge (%d,%d) in MST\n", ea->e[i]->vid1, ea->e[i]->vid2);
			union2(g, ea->e[i]->vid1, ea->e[i]->vid2);
	    }
    }
}

main(int argc, char *argv[])
{
	graph g;
	edgearr e;
	int und = TRUE;

	read_graph(&g, und);
	print_graph(&g);

	graph_to_array(&g, &e, und);
	print_array(&e);
	sort_array(&e);
	print_array(&e);

	kruskal(&g, &e);

}

