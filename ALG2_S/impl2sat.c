#include <stdio.h>
#include <stdlib.h>

#define NMAX 1000000
#define TRUE 1
#define FALSE 0

#define UNEX 0
#define EXPL 1
#define PROC 2

typedef struct  {
    struct vertex *next;       /* adjacency list                 */
    int vid;                   /* vertex id                      */
} vertex;

typedef struct {
    int directed;              /* 0 - undirected, 1 - directed    */
    int n;                     /* # of vertices                   */
    int m;                     /* # of edges                      */
    vertex **v;                /* graph array                     */
    int *ex;                   /* vertex status 0 - not explored  */
                               /*               1 - explored      */
                               /*               2 - processed     */
    int *stack;                /* process stack                   */
    int stp;                   /* index to stack last element     */
    int *f;                    /* finished time for 1st pass      */
                               /* index to vertex for 2nd pass    */
    int *scclist;              /* strongly connected components   */
    int nscc;                  /* number of SCCs                  */
} graph;

int debug;
int explored;
int count;

int fintime;   /* SCC - finishing times in 1st pass */
int leader;    /* SCC - leaders in 2nd pass         */

int sig2par(int x)
{
	if (x == 0) {
		printf("SIG2PAR ERROR\n");
		return (-1);
	}
     if (x < 0)
         return (-2*x-1);
     if (x > 0)
         return (2*x);
     return (-1);
}

int par2sig(int x)
{
	 if (x <= 0) {
		 printf("SIG2PAR ERROR\n");
		 return (-1);
     }
     if (x%2 == 0)
         return (x/2);
     if (x%2 == 1)
         return (-1*(x+1)/2);
     return (-1);
}


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

int initg(graph *g, int maxel)
{
	int i;           /* counter */
	int status;

    status = TRUE;

    g->v  = malloc(maxel*sizeof(struct vertex *));
    g->ex = malloc(maxel*sizeof(int));
    g->stack = malloc(maxel*sizeof(int));
    g->f  = malloc(maxel*sizeof(int));
    g->scclist  = malloc(maxel*sizeof(int));
	g->n = 0;
	g->m = 0;
	g->directed = 0;
	g->stp = -1;
	g->nscc = 0;

	for (i=0; i < maxel; i++) {
		g->f[i] = 0;            /* process order     */
		g->ex[i] = UNEX;        /* explored vertex   */
		g->stack[i] = 0;        /* proces stack      */
	    g->v[i] = NULL;         /* vertex pointer    */
	    g->scclist[i] = 0;      /* SCC list          */
    }
    if (g->v == NULL || g->ex == NULL || g->stack == NULL || g->f == NULL || g->scclist == NULL) return (FALSE);
    return (TRUE);
}

#define MAXLINE 30

int readg(char *file, graph *g, graph *gx, int inverse)
{
    char str[MAXLINE];
    char delims[] = " \n";
    char *temp;
    int i1, i2, i3, maxel, stat, i1x, i2x, i;
    vertex *p, *q;
    FILE *in;
    int status;

    status = TRUE;
    in= fopen(file, "r");

    fgets(str,MAXLINE,in);
	maxel = atoi((char *)strtok( str, delims ));
    printf("ELEMENTS=%d\n", maxel);

    stat = initg(g, 2*maxel);
	if (stat == FALSE) { printf("initg: malloc error. exit"); return stat; }

    while (fgets(str,MAXLINE,in) != NULL) {
		temp = (char *) strtok( str, delims );
		if (temp == NULL) { printf ("ERROR readg token #1\n"); fclose(in); break; }
        i1x = atoi(temp);
		if (temp == NULL) { printf ("ERROR readg token #2\n"); fclose(in); break; }
		temp = (char *) strtok( NULL, delims );
        i2x = atoi(temp);
		for(i=0; i<2; i++) {          /* TRANSFORMATION (X OR Y) TO (((NOT X) IMPLIES Y) AND ((NOT Y) IMPLIES X)) */
			if (i == 0) {
                i1 = sig2par(-1*i1x);
                i2 = sig2par(i2x);
			}
			else {
                i1 = sig2par(-1*i2x);
                i2 = sig2par(i1x);
			}
			printf("%d %d\n", i1, i2);
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
	fclose(in);
	return (status);
}

void main(int argc, char *argv[])
{
    graph g, ginv;
    int stat;

    debug = FALSE;
    if (argc < 2) { printf("%s: missing file name"); exit; }
    if (argc == 3 && argv[2][0] == 'D') debug = TRUE;

    stat = readg(argv[1], &g, NULL, FALSE);
    printg(&g);
}