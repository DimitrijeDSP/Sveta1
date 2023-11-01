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

prim(graph *g, int start)           /* PRIM MINIMUM SPANNING TREE */
{
	int i;                          /* counter */
	edgenode *p;                    /* temporary pointer */
	int v;                          /* current vertex to process */
	int w;                          /* candidate next vertex */
	int weight;                     /* edge weight */
	int dist;                       /* best current distance from start */
	bool intree[MAXV+1];            /* is the vertex int the tree yet? */
	int distance[MAXV+1];           /* cost of adding to tree */
    double total;                   /* total distance */

    for (i=1; i<=g->nvertices; i++) {
		intree[i] = FALSE;
		distance[i] = MAXINT;
		parent[i] = -1;
    }

    distance[start] = 0;
    v = start;

    total = 0;
    while (intree[v] == FALSE) {
	    total = total + (double) distance[v];
        printf("distance[%d]=%d, total=%20.0f\n", v,distance[v],total);
        intree[v] = TRUE;
        p = g->edges[v];
        while (p != NULL) {
			w = p->y;
			weight = p->weight;
			if ((distance[w] > weight) && (intree[w] == FALSE)) {
				distance[w] = weight;
				parent[w] = v;
			}
			p = p->next;
		}

		v = 1;
		dist = MAXINT;
		for (i=1; i<=g->nvertices; i++) {
		    if ((intree[i] == FALSE) && (dist > distance[i])) {
				dist = distance[i];
				v = i;
			}
	    }
	}
	printf("total=%20.0f\n",total);
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

	printf("========== prime min spanning tree =============\n");
	prim(&g,1);
}




