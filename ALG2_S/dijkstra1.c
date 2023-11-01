/* SAME AS DIJKSTRA.C BUT READ STANDARD INPUT GRAPH FORMAT */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXINT INT_MAX

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

printsp(graph *g)
{
	int i;

	printf("----------------------------------\n");
	printf("n=%d\n", g->n);
	printf("----------------------------------\n");
	for (i=0; i<g->n; i++) {
		printf("vertex id=%d [%d], A[%d]=%d\n", g->v[i], i, i, g->A[i]);
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
	g->n = nx;
	g->m = 0;

	for (i=0; i < nx; i++) {
		g->X[i] = 0;
		g->B[i] = 0;
		g->A[i] = 0;
	    g->v[i] = NULL;         /* vertex pointer    */
    }
}

readg(graph *g)
{
	vertex *p, *q;
	int nn, mm, n1, n2, wx;
	g->n=0;
	scanf("%d %d", &nn, &mm);
	initg(g,nn);

	while (scanf("%d %d %d",&n1, &n2, &wx) > 0)
	{
        g->m++;
        insert_graph(g, n1, n2, wx);
    }
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

printx(graph *g)
{
	int i;
    int x[] = {7,37,59,82,99,115,133,165,188,197};

    for (i=0; i<10; i++)
		printf("%d,",g->A[ x[i]-1 ]);
	printf("\n");
}

void main(int argc, char *argv[])
{
    graph g;

    readg(&g);
    printg(&g);

    dijkstra(&g,1);
    printsp(&g);
    printx(&g);
}