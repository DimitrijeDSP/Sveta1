#include <stdio.h>
#include <stdlib.h>

#define NMAX 1000000
#define TRUE 1
#define FALSE 0

typedef struct  {
    struct vertex *next;       /* adjacency list                 */
    int vid;                   /* vertex id                      */
} vertex;

typedef struct {
    int directed;              /* 0 - undirected, 1 - directed   */
    int n;                     /* # of vertices                  */
    int m;                     /* # of edges                     */
    vertex **v;                /* graph array                    */
    int *ex;                   /* explored vertex                */
    int *pr;                   /* explored vertex                */
    int *de;                   /* vertex degree                  */
} graph;


printg(graph *g)
{
	int i;
	vertex *p;

	printf("----------------------------------\n");
	printf(" n=%d\n", g->n);
	printf("----------------------------------\n");
	for (i=0; i<g->n; i++) {
		if (g->v[i] == NULL) continue;
		printf("vertex id=%d [%d]\n", g->v[i]->vid, i);
        p = (vertex *) g->v[i]->next;
		while (p != NULL) {
			printf("%d ",p->vid);
			p = (vertex *) p->next;
	    }
	    printf("\n");
    }
}

initg(graph *g)
{
	int i;           /* counter */

    g->v  = malloc(NMAX*sizeof(struct vertex *));
    g->ex = malloc(NMAX*sizeof(int));
    g->pr = malloc(NMAX*sizeof(int));
    g->de = malloc(NMAX*sizeof(int));
	g->n = 0;
	g->m = 0;
	g->directed = 0;

	for (i=0; i < NMAX; i++) {
		g->de[i] = 0;           /* vertex degree     */
		g->ex[i] = FALSE;       /* explored vertex   */
		g->pr[i] = FALSE;       /* processed vertex  */
	    g->v[i] = NULL;         /* vertex pointer    */
    }
}

#define MAXLINE 30

readg(graph *g)
{
    char str[MAXLINE];
    char delims[] = " \n";
    int i1, i2;
    vertex *p, *q;

    while (fgets(str,MAXLINE,stdin) != NULL) {
        i1 = atoi((char *) strtok( str, delims ));
        i2 = atoi((char *) strtok( NULL, delims ));
        if (g->v[i1-1] == NULL) {
			p = (vertex *) malloc(sizeof(vertex));
			g->v[i1-1] = p;
			p->vid = i1;
			p->next = NULL;
			g->n++;
	    }
        p = (vertex *) malloc(sizeof(vertex));
        p->vid = i2;
        g->m++;
		q = (vertex *) g->v[i1-1]->next;
        g->v[i1-1]->next = (struct vertex *) p;
	    p->next = (struct vertex *) q;
        if (g->v[i2-1] == NULL) {
			p = (vertex *) malloc(sizeof(vertex));
			g->v[i2-1] = p;
			p->vid = i2;
			p->next = NULL;
			g->n++;
	    }
	}
}

DFS(graph *g, int s)
{
	int i;
	vertex *p;

    i = s-1;
	if (g->v[i] == NULL) return;
	g->ex[i] = TRUE;
	printf("DFS vertex id=%d [%d]\n", g->v[i]->vid, i);
    p = (vertex *) g->v[i]->next;
	while (p != NULL) {
		i = p->vid - 1;
		printf("+++ vertex %d \n",p->vid);
		if (g->ex[i] == FALSE) DFS(g,p->vid);
		p = (vertex *) p->next;
	}
}



void main(int argc, char *argv[])
{
    graph g;

    initg(&g);
    readg(&g);
    printg(&g);
    printf("n=%d m=%d\n",g.n,g.m);
    DFS(&g,1);
}