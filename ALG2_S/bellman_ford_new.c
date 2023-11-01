
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXINT 21474800

#define TRUE 1
#define FALSE 0

typedef struct  {
    int vid;                   /* vertex id      */
    int ew;                    /* edge weight    */
    struct vertex *next;       /* adjacency list */
} vertex;

typedef struct {
    int n;              /* # of vertices  */
    int m;              /* # of edges     */
    vertex **v;         /* graph array    */
    int *X;             /* verices processed so far (boolean) */
    int ix;             /* count of vertices processed so far */
    int *A;             /* computed shortest path distances */
    int *B;             /* computed shortest paths (parent list) */
    int *dist;          /* BELLMAN FORD DISTANCE */
} graph;

printg(graph *g)
{
	int i;
	vertex *p;

	printf("----------------------------------\n");
	printf("n=%d\n", g->n);
	printf("----------------------------------\n");
	for (i=0; i<g->n; i++) {
		printf("vertex id=%d [%d]\n", g->v[i]->vid, i);
        p = (vertex *) g->v[i]->next;
		while (p != NULL) {
			printf("%d,%d ",p->vid,p->ew);
			p = (vertex *) p->next;
	    }
	    printf("\n");
    }
}

printsp(graph *g, int mode)   /* mode - 0 DIJKSTRA, mode 1 - BELLMAN FORD */
{
	int i;

	printf("----------------------------------\n");
	printf("n=%d\n", g->n);
	printf("----------------------------------\n");
	for (i=0; i<g->n; i++) {
		if (mode == 0)
		    printf("vertex id=%d [%d], A[%d]=%d\n", g->v[i], i, i, g->A[i]);
        else
		    printf("vertex id=%d [%d], dist[%d]=%d\n", g->v[i], i, i, g->dist[i]);
    }
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
        p->ew = 0;
    }
    q = (vertex *) malloc(sizeof(vertex));
    q->vid = n2;
    q->ew = wx;
    q->next = p->next;
    p->next = (struct vertex *) q;
}

initg(graph *g, int nx)
{
	int i;           /* counter */

    g->v  = malloc(nx*sizeof(struct vertex *));
    g->A = malloc(nx*sizeof(int));
    g->B = malloc(nx*sizeof(int));
    g->X = malloc(nx*sizeof(int));
    g->dist = malloc(nx*sizeof(int));
	g->n = nx;
	g->m = 0;

	for (i=0; i < nx; i++) {
		g->X[i] = 0;
		g->B[i] = 0;
		g->A[i] = 0;
		g->dist[i] = 0;
	    g->v[i] = NULL;         /* vertex pointer    */
    }
}

readg(graph *g)
{
	vertex *p, *q;
	int nn, mm, n1, n2, wx;
	g->n=0;
	scanf("%d %d", &nn, &mm);
	printf("nn=%d mm=%d\n", nn, mm);
	initg(g,nn);

	while (scanf("%d %d %d",&n1, &n2, &wx) > 0)
	{
        g->m++;
        insert_graph(g, n1, n2, wx);
    }
}

/*    The main function that finds shortest distances from src to all other vertices */
/*    using Bellman-Ford algorithm.  The function also detects negative weight cycle */

void bellman_ford(graph * g, int src)
{
    int V = g->n;
    int E = g->m;
    int i, j, u, v, u1, v1, weight;
	vertex *p;
	int odd, jstart, jstep;

    /* Step 1: Initialize distances from src to all other vertices as INFINITE  */
    for (i = 0; i < V; i++)
        g->dist[i] = MAXINT;
    g->dist[src-1] = 0;
    printf("step 1 finished\n");

    /* Step 2: Relax all edges |V| - 1 times. A simple shortest path from src   */
    /* to any other vertex can have at-most |V| - 1 edges                       */
    for (i = 0; i < V; i++) {
		jstart = 0;
		jstep = 1;
		if ( i % 2 == 0) {
			odd = TRUE;      /* vertex numvers are from 1..n    */
		    jstart = 0;      /* array indices are from 0..(n-1) */
		    jstep = 1;
		}
		else {
			odd = FALSE;
		    jstart = V-1;
		    jstep = -1;
	    }
        for (j = jstart; 0 <= j && j < V; j=j+jstep) {
            p = (vertex *) g->v[j]->next;
  		    while (p != NULL) {
                u = g->v[j]->vid; u1 = u - 1;
                v = p->vid;  v1 = v - 1;
                weight = p->ew;
                if ((odd == TRUE && u < v) || (odd == FALSE && u > v)) {
                    if (g->dist[u1] + weight < g->dist[v1])
                        g->dist[v1] = g->dist[u1] + weight;
				}
                p = (vertex *) p->next;
	        }
        }
    }
    printf("step 2 finished\n");

    /* Step 3: check for negative-weight cycles.  The above step guarantees     */
    /* shortest distances if graph doesn't contain negative weight cycle.       */
    /* If we get a shorter path, then there is a cycle.                         */

    for (j = 0; j < V; j++) {
         p = (vertex *) g->v[j]->next;
 	    while (p != NULL) {
            u = g->v[j]->vid; u1 = u - 1;
            v = p->vid; v1 = v - 1;
            weight = p->ew;
            if (g->dist[u1] + weight < g->dist[v1]) {
                printf("Graph contains negative weight cycle");
                break;
			}
            p = (vertex *) p->next;
        }
    }
    printf("step 3 finished\n");
}


dijkstra(graph *g, int s)
{
	int i,j,is,len,ip;
	vertex *p;


    for (i = 0; i < g->n; i++) {
		g->X[i] = FALSE;
		g->A[i] = MAXINT;
		g->B[i] = -1;
	}

    is = s-1;             /* start from vertex s */
    g->A[is] = 0;

    while (g->X[is] == FALSE) {
		g->X[is] = TRUE;
        p = (vertex *) g->v[is]->next;
		while (p != NULL) {
            ip = p->vid - 1;
			len = p->ew;
			if (g->A[ip] > g->A[is]+len) {
				g->A[ip] = g->A[is]+len;
				g->B[ip] = is+1;
		    }
			p = (vertex *) p->next;
	    }

        is = 0;             /* find next vertex - greedy way */
        len = MAXINT;
        for (i = 0; i < g->n; i++) {
			if (g->X[i] == FALSE && len > g->A[i]) {
				len = g->A[i];
				is = i;
		    }
	    }
    }
}

printx(graph *g, int mode)
{
	int i;
    int x[] = {7,37,59,82,99,115,133,165,188,197};

    for (i=0; i<10; i++) {
        if (mode == 0)
		    printf("%d,",g->A[ x[i]-1 ]);
		else
		    printf("%d,",g->dist[ x[i]-1 ]);
	}
	printf("\n");
}

shortest_path(graph *g, int start, int mode)
{
	if (mode == 0)
	    dijkstra(g, start);
	else
	    bellman_ford(g, start);
}


void main(int argc, char *argv[])
{
    int mode = 0, debug = TRUE;
    graph g;

    if (argc == 2 && argv[1][0] == 'B') mode = 1;

    readg(&g);
    if (debug == TRUE) printf("READ GRAPH FINISHED\n");
    if (debug == TRUE) printg(&g);

    shortest_path(&g,1, mode);
    if (debug == TRUE) printsp(&g, mode);
    printx(&g, mode);

}