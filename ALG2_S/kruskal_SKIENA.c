#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXINT INT_MAX
typedef int bool;
#define TRUE 1
#define FALSE 0

#define MAXV 1000    /* maximum number of vertices */

bool processed[MAXV+1];         /* which vertices have been processed */
bool discovered[MAXV+1];        /* which vertices have been found */
int parent[MAXV+1];             /* discovery relation */

typedef struct {
	int y;                      /* adjancency info */
	int weight;                 /* edge weight, if any */
	struct edgenode *next;      /* next edge in list */
} edgenode;

typedef struct {
	edgenode *edges[MAXV+1];    /* adjancency info */
	int degree[MAXV+1];         /* outdegree of each vertex */
	int nvertices;              /* number of vertices in graph */
	int nedges;                 /* number of edges in graph */
	bool directed;              /* is it graph directed */
} graph;

#define SET_SIZE 100

typedef struct {
	int p[SET_SIZE+1];         /* parent element                */
	int size[SET_SIZE+1];      /* number of elements in subtree */
	int n;                     /* number of elements in set     */
} set_union;

set_union_init(set_union *s, int n)
{
	int i;                      /* counter */

	for (i=1; i<=n; i++) {
		s->p[i] = i;
		s->size[i] = 1;
	}

	s->n = n;
}

int find(set_union *s, int x)
{
	if (s->p[x] == x)
	    return (x);
	else
	    return ( find(s, s->p[x]) );
}

int union_sets(set_union *s, int s1, int s2)
{
	int r1, r2;         /* root of sets */

	r1 = find(s, s1);
	r2 = find(s, s2);

	if (r1 == r2) return;       /* already in same set */

	if (s->size[r1] >= s->size[r2]) {
		s->size[r1] = s->size[r1] + s->size[r2];
		s->p[ r2 ] = r1;
	}
	else {
		s->size[r2] = s->size[r1] + s->size[r2];
		s->p[ r1 ] = r2;
	}
}

bool same_component (set_union *s, int s1, int s2)
{
	return ( find(s,s1) == find(s,s2) );
}


initialize_graph(graph *g, bool directed)
{
	int i;           /* counter */

	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;

	for (i=1; i<=MAXV; i++) g->degree[i] = 0;
	for (i=1; i<=MAXV; i++) g->edges[i] = NULL;
}

insert_edge(graph *g, int x, int y, int w, bool directed)
{
	edgenode *p;                    /* temporary pointer */

	p = malloc(sizeof(edgenode));   /* allocate edgenode storage */

	p->weight = w;
	p->y = y;
	p->next = g->edges[x];

	g->edges[x] = p;                /* insert at head of list */
	g->degree[x] ++;

	if (directed == FALSE)
	    insert_edge(g,y,x,w,TRUE);
	else
	    g->nedges ++;
}


read_graph(graph *g, bool directed)
{
	int i;                /* counter */
	int m;                /* number of edges */
	int x, y, w;          /* vertices in edge (x,y) and weight */

	initialize_graph(g, directed);

	scanf("%d %d",&(g->nvertices),&m);

	for (i=1; i<=m; i++) {
	     scanf("%d %d %d",&x,&y,&w);
	     insert_edge(g,x,y,w,directed);
    }
}


print_graph(graph *g)
{
	int i;            /* counter */
	edgenode *p;      /* temporary pointer */

	for (i=1; i<=g->nvertices; i++) {
	    printf("GRAPH %d ", i);
	    p = g->edges[i];
	    while (p != NULL) {
			printf(" %d", p->y);
			p = p->next;
	    }
	    printf("\n");
    }
}

typedef struct {
	int x;
	int y;
	edgenode *xp;
	edgenode *yp;
	int weight;
} edge_pair;

to_edge_array(graph *g, edge_pair *e)
{
	int i,j;          /* counter */
	edgenode *p;      /* temporary pointer */

    j=1;
	for (i=1; i<=g->nvertices; i++) {
	    p = g->edges[i];
	    while (p != NULL) {
		    e[j].x = i;
	        e[j].xp = p;
 		    e[j].y = p->y;
	        e[j].weight = p->weight;
	        e[j].yp = p->next;
			p = p->next;
			j++;
	    }
    }
}

print_edge_array(edge_pair *e, int n)
{
	int j;          /* counter */

    for (j=1;j<=n; j++)
	    printf("edge_array [%d] x=%d y=%d weight=%d\n", j,e[j].x, e[j].y, e[j].weight);
}

static int weight_compare(const void *i, const void *j)
{
	edge_pair *ii, *jj;
	ii = (edge_pair *) i;
	jj = (edge_pair *) j;

	if (ii->weight > jj->weight) return(1);
	if (ii->weight < jj->weight) return(-1);
	return(0);
}

kruskal (graph *g)
{
	int i;                       /* counter */
	set_union s;                 /* set union data structure */
	edge_pair e[MAXV+1];         /* array of edges data structure */

	set_union_init(&s, g->nvertices);

	to_edge_array(g, e);         /* sort edges by increasing cost */
	printf("BEFORE QSORT\n");
    print_edge_array(e, g->nedges);
	qsort(&e, g->nedges+1, sizeof(edge_pair), weight_compare);
	printf("AFTER QSORT\n");
    print_edge_array(e, g->nedges);
	printf("AFTER PRINT\n");

	for (i=1; i<=(g->nedges); i++) {
		if (same_component(&s, e[i].x, e[i].y) != TRUE) {
			printf("edge (%d,%d) in MST\n", e[i].x, e[i].y);
			union_sets(&s, e[i].x, e[i].y);
	    }
    }
}

main(int argc, char *argv[])
{
	graph g;
	int i, ix;
	bool bx;    /* bx - directed or undirected */

	printf("=============== DFS graph type =================\n");
	scanf("%d",&ix);
	bx = FALSE;
	if (ix == 1) bx = TRUE;
	if (bx == TRUE)  printf("DIRECTED GRAPH\n"); else printf("UNDIRECTED GRAPH\n");

	printf("========== adjancency vertices =============\n");
	read_graph(&g,bx);
	print_graph(&g);

	printf("========== kruskal min spanning tree =============\n");
	kruskal(&g);
}

