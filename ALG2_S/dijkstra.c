#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXINT INT_MAX

#define TRUE 1
#define FALSE 0

#define NMAX 1000

typedef struct  {
    int vid;                   /* vertex id      */
    int ew;                    /* edge weight    */
    struct vertex *next;       /* adjacency list */
} vertex;

typedef struct {
    int n;               /* # of vertices  */
    int m;               /* # of edges     */
    vertex *v[NMAX];     /* graph array    */
    int X[NMAX];         /* verices processed so far (boolean) */
    int ix;              /* count of vertices processed so far */
    int A[NMAX];         /* computed shortest path distances */
    int B[NMAX];         /* computed shortest paths (parent list) */
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

printg1(graph *g)
{
	int i;
	vertex *p;

	printf("------- START ---------------------\n");
	printf("%d %d\n", g->n, g->m);
	for (i=0; i<g->n; i++) {
        p = (vertex *) g->v[i]->next;
		while (p != NULL) {
			printf("%d %d %d\n",g->v[i]->vid, p->vid, p->ew);
			p = (vertex *) p->next;
	    }
    }
	printf("------- STOP ---------------------\n");
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

#define MAXLINE 1000

readg(graph *g)
{

    char str[MAXLINE];
    char delims[] = "\t\n";
    char * result = NULL;
    int temp,it1,it2;
    int ntemp, nlist;
    vertex *p, *q;
    int start;

    g->n=0;
    g->m=0;
    nlist=0;
    start=0;
    while (fgets(str,MAXLINE,stdin) != NULL) {
        result = (char *) strtok( str, delims );
        while( result != NULL ) {
             q = (vertex *) malloc(sizeof(vertex));
             if (start == 0) {
				 p = q;
                 g->v[g->n] = p;
		     }
		     else {
                 p->next = (struct vertex *) q;
                 g->m++;
		     }
             p = q;
             p->next = NULL;
             if (start == 0) {
                 it1 = atoi(result);
                 it2 = 0;
                 start = 1;
		     }
             else
                 sscanf(result,"%d,%d",&it1,&it2);
             p->vid = it1;
             p->ew = it2;
             result = (char *) strtok( NULL, delims );
        }
        g->n++;
        start=0;
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