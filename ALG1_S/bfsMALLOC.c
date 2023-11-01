#include <stdio.h>
#include <stdlib.h>

#define NMAX 1000000

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
    int *pr;                   /* processed vertex               */
    int *de;                   /* vertex degree                  */
} graph;


printg(graph *g)
{
	int i;
	vertex *p;

	printf("----------------------------------\n");
	printf("n=%d\n", g->n);
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
    vertex *r;
    int *ip;

    g->v = (vertex **) malloc(NMAX * sizeof(vertex *));
    g->ex = (int *) malloc (NMAX * sizeof(int));
    g->pr = (int *) malloc (NMAX * sizeof(int));
    g->de = (int *) malloc (NMAX * sizeof(int));
	g->n = 0;
	g->m = 0;
	g->directed = 0;

	for (i=0; i <= NMAX; i++) {
        ip = (g->de)+i;
		*ip = 0;
		ip = (g->ex)+i;
		*ip = 0;
		ip = (g->pr)+i;
		*ip = 0;
        r = *(g->v+i);
	    r = NULL;
    }
}

#define MAXLINE 30

readg(graph *g)
{
    char str[MAXLINE];
    char delims[] = " \n";
    int i1, i2;
    vertex *p, *q, *r;

    printf ("aa\n");
    while (fgets(str,MAXLINE,stdin) != NULL) {
        i1 = atoi((char *) strtok( str, delims ));
        i2 = atoi((char *) strtok( NULL, delims ));
        printf ("(%d)->(%d)\n",i1,i2);
        r = *(g->v+i1-1);
        if (r == NULL) {
			p = (vertex *) malloc(sizeof(vertex));
			r = p;
			p->vid = i1;
			p->next = NULL;
			g->n++;
	    }
        p = (vertex *) malloc(sizeof(vertex));
        p->vid = i2;
        g->m++;
		q = (vertex *) r->next;
        r->next = (struct vertex *) p;
	    p->next = (struct vertex *) q;
        r = *(g->v+i2-1);
        if (r == NULL) {
			p = (vertex *) malloc(sizeof(vertex));
			r = p;
			p->vid = i2;
			p->next = NULL;
			g->n++;
	    }
	}
}

void main(int argc, char *argv[])
{
    graph g;

    initg(&g);
    readg(&g);
    printg(&g);
}