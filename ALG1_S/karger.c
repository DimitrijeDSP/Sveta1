#include <stdio.h>
#include <stdlib.h>

#define NMAX 1000

typedef struct  {
    int vid;                   /* vertex id      */
    struct vertex *next;       /* adjacency list */
} vertex;

typedef struct {
    int n;               /* # of vertices  */
    int m;               /* # of edges     */
    vertex *v[NMAX];     /* graph array    */
} graph;


contract(graph *g, int i, int j)  /* i, j are vertex order numbers in graph main array */
{
	vertex *p;
    int ii,jj;

    /* FIND VERTEX IDs */
    ii = g->v[i]->vid;
    jj = g->v[j]->vid;

    if (g->n <= 2) return;          /* only if n > 2 !!! */

    /* CONTRACT OPERATION */
    p= (vertex *) g->v[i]->next;
    while (p->next != NULL)         /* find the end of linked list for node i   */
		p = (vertex *) p->next;
    p->next = g->v[j]->next;        /* join j-th node with i-th node            */
    if (j != g->n-1)
        g->v[j] = g->v[g->n-1];     /* remove j-th node (replace with last one) */
    g->v[g->n-1] = NULL;
    g->n--;
}

cleanup(graph *g, int i, int j)  /* i, j are vertex ids */
{
	vertex *p1, *p2;
    int k;

    /* CLEANUP OPERATION */
    for (k=0; k<g->n; k++) {
        p1 = g->v[k];
        p2 = (vertex *) p1->next;
        while (p2 != NULL) {
		    if (p2->vid == j) p2->vid = i;     /* replace j vertex with i vertex */
	        p2 = (vertex *) p2->next;
        }
    }
}

rmloops(graph *g)
{
	vertex *p1, *p2;
    int k,ii;

    /* REMOVE SELF LOOPS OPERATION */
    for (k=0; k<g->n; k++) {
        ii = g->v[k]->vid;
        p1 = g->v[k];
        p2 = (vertex *) p1->next;
        while (p2 != NULL) {
		    if (p2->vid == ii) {          /* remove duplicate */
	           if (p2->next == NULL) {
	               p1->next = NULL;
	               break;
		       }
	           else {
	               p1->next = p2->next;
	               p2 = (vertex *) p1->next;
		       }
		    }
		    else {
               p1 = p2;
               p2 = (vertex *) p1->next;
		    }
        }
    }
}

int findp(graph *g, int i)         /* for given vertex id - return position */
{
	int k;
	for (k=0; k<g->n; k++) {
	   if (g->v[k]->vid == i)
	       return (k);
    }
	return (-1);
}

mincut(graph *g)
{
	 vertex *p;
	 int n,id_i,pos_i,id_j,pos_j;

     n = g->n;
	 while (n > 2) {
		  printf("mincut n=%d\n",n);
		  srand(time(NULL));
	      pos_i = rand() % n;                    /* random position i        */
	      id_i = g->v[pos_i]->vid;               /* i-th vertex id           */
	      p = (vertex *) g->v[pos_i]->next;      /* adjancent vertex pointer */
	      if (p == NULL) { printf("error 1\n"); continue; }
	      id_j = p->vid;                         /* j-th vertex id           */
          if (id_j < 0) { printf("error 2\n"); continue; }
          pos_j = findp(g,id_j);
          if (pos_j < 0) { printf("error 3 , pos_j=%d id_j=%d\n", pos_j,id_j); continue; }
          if (pos_j >= n) { printf("error 4\n"); continue; }
		  printf("mincut n=%d pos_i=%d pos_j=%d\n",n,pos_i,pos_j);
		  if (pos_i == pos_j) { printf("error 5\n"); continue; }
          contract(g, pos_i, pos_j);
          cleanup(g, id_i, id_j);
          rmloops(g);
          n = g->n;
     }
}


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
			printf("%d ",p->vid);
			p = (vertex *) p->next;
	    }
	    printf("\n");
    }
}

countg(graph *g)
{
	int i, count;
	vertex *p;

	printf("----------------------------------\n");
	printf("n=%d\n", g->n);
	printf("----------------------------------\n");
	for (i=0; i<g->n; i++) {
        count=0;
        p = (vertex *) g->v[i]->next;
		while (p != NULL) {
			count++;
			p = (vertex *) p->next;
	    }
		printf("vertex id=%d [%d], count=%d\n", g->v[i]->vid, i, count);
    }
}

#define MAXLINE 1000

readg(graph *g)
{

    char str[MAXLINE];
    char delims[] = "\t\n";
    char * result = NULL;
    int temp;
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
                 start = 1;
		     }
		     else {
                 p->next = (struct vertex *) q;
                 g->m++;
		     }
             p = q;
             p->next = NULL;
             p->vid = atoi(result);
             result = (char *) strtok( NULL, delims );
        }
        g->n++;
        start=0;
    }
}

void main(int argc, char *argv[])
{
    graph g;

    readg(&g);
    printg(&g);
    mincut(&g);
    printf("========= MIN CUT ======\n");
    printg(&g);
    printf("========= MIN CUT ======\n");
    countg(&g);
}