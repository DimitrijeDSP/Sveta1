/* FROM STEVEN SKIENA BOOK WITH CORRECTIONS  */
/* 6.3 SHORTEST PATHS, "FLOYD" ALG, PAGE 211 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXINT 10007    /* max int */
typedef int bool;
#define TRUE 1
#define FALSE 0

typedef struct {
	int ***weight;                    /* adjacency/weight info */
	int nvertices;                    /* number of vertices in graph */
} adjacency_matrix;

int initialize_adjm(adjacency_matrix *g, int n)
{
	int i,j,k;           /* counter */

    g->weight = (int ***) malloc(sizeof(int **)*(n+1));
    if (g->weight == NULL) return (FALSE);

	for (i=0; i<=n; i++) {
	   g->weight[i] = (int **) malloc(sizeof(int *)*(n+1));
       if (g->weight[i] == NULL) return (FALSE);
	   for (j=0; j<=n; j++) {
	       g->weight[i][j] = (int *) malloc(sizeof(int)*(n+1));
	       for (k=0; k<=n; k++) {
	           g->weight[i][j][k] = MAXINT;
		   }
	   }
	}
	return (TRUE);
}

int read_adjm(adjacency_matrix *g, bool directed)
{
	int i,j,k;            /* counters */
	int m;                /* number of edges */
	int x, y, w;          /* vertices in edge (x,y) and weight */

	scanf("%d %d",&(g->nvertices),&m);
	printf("%d %d\n",(g->nvertices),m);

	printf("========== initialize graph =============\n");
	if (initialize_adjm(g, g->nvertices) == FALSE) return (FALSE);
	printf("========== initialize graph DONE =============\n");

	for (i=1; i<=g->nvertices; i++) {
	    for (j=1; i<=g->nvertices; i++) {
	         g->weight[i][j][0] = MAXINT;
		}
	}
	printf("========== loop 1 done =============\n");

	for (i=1; i<=m; i++) {
	     scanf("%d %d %d",&x,&y,&w);
	     g->weight[x][y][0] = -1;
	     g->weight[y][x][0] = 0;
    }
	printf("========== loop 2 done =============\n");
	for (i=1; i<=g->nvertices; i++) {
	     g->weight[i][i][0] = 0;
    }
    printf("========== loop 3 done =============\n");

    return (TRUE);
}

print_adjm(adjacency_matrix *g, int k)
{
	int i,j;            /* counter */

	for (i=1; i<=g->nvertices; i++) {
	    for (j=1; j<=g->nvertices; j++)
             printf("| %10d ",g->weight[i][j][k]);
        printf(" |\n");
    }
}

int min_distance(adjacency_matrix *g, int k)
{
	int i,j;            /* counter */
    int min;
    int nc = FALSE;

    min = MAXINT;
	for (i=1; i<=g->nvertices; i++) {
		if (nc == TRUE) break;
	    for (j=1; j<=g->nvertices; j++) {
	         if (i == j) {
                 if (g->weight[i][i][k] < 0) {
                     nc = TRUE;
			         break;
		         }
				 continue;
			 }
             if (g->weight[i][j][k] < min) min = g->weight[i][j][k];
	    }
    }
    if (nc == TRUE) min = MAXINT;
    return (min);
}

floyd(adjacency_matrix *g)
{
	int i,j;          /* dimension counters */
	int k;            /* intermediate vertex counter */
	int through_k;    /* distance through vertex k */

	for (k=1; k<=g->nvertices; k++)
	    for (i=1; i<=g->nvertices; i++)
	          for (j=1; j<=g->nvertices; j++) {
				  through_k = g->weight[i][k][k-1]+g->weight[k][j][k-1];
				  if (through_k < g->weight[i][j][k-1])
				      g->weight[i][j][k] = through_k;
				  else
				      g->weight[i][j][k] = g->weight[i][j][k-1];
			  }
}

print_graph(adjacency_matrix *g, int k)
{
	int i,j;			/* counters */

	for (i=1; i<=g->nvertices; i++) {
		printf("%d: ",i);
		for (j=1; j<=g->nvertices; j++)
			if (g->weight[i][j][k] < MAXINT)
				printf(" %d",j);
		printf("\n");
	}
}

main(int argc, char *argv[])
{
	adjacency_matrix g;

    int debug = FALSE;
	int ix, md;
	bool bx;    /* bx - directed or undirected */

	printf("=============== DFS graph type =================\n");
	/* scanf("%d",&ix);  */
 	bx = FALSE;
	if (ix == 1) bx = TRUE;
    bx = TRUE;
	if (bx == TRUE)  printf("DIRECTED GRAPH\n"); else printf("UNDIRECTED GRAPH\n");

	printf("========== read graph =============\n");
	if (read_adjm(&g,bx) == FALSE) {
		printf("read_adjm failed\n");
		return;
	}
	printf("========== print graph =============\n");
	if (debug == TRUE) print_graph(&g,g.nvertices);
	printf("========== print adjacency matrix =============\n");
	if (debug == TRUE) print_adjm(&g,g.nvertices);
	printf("========== FLOYD min spanning tree =============\n");
	floyd(&g);
	printf("========== print graph =============\n");
	if (debug == TRUE || TRUE == TRUE) print_adjm(&g,g.nvertices);
	printf("========== min distance =============\n");
	md = min_distance(&g,g.nvertices);
    if (md == MAXINT)
       printf("NEGATIVE CYCLE FOUND !!!\n");
    else
       printf("MINIMUM DISTANCE = %d \n", md);
}

