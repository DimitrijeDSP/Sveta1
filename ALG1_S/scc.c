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

int intcompare(const void *i, const void *j)
{
	int *ii, *jj;
	ii = (int *) i;
	jj = (int *) j;
	if (*ii > *jj) return(1);
	if (*ii < *jj) return(-1);
	return(0);
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

int countg(graph *g)
{
	int i, nex;

    nex = 0;
	for (i=0; i<g->n; i++) {
		if (g->v[i] == NULL) continue;
		if (g->ex[i] == PROC) nex++;
    }
    return (nex);
}

printscc(graph *g)
{
	int i,j,k,max;
    int x[5];
    int skeep;

    for (j=0; j<5; j++) {
        max = 0;
	    for (i=0; i<g->nscc; i++) {
			skeep = 0;
			for (k=0; k<j; k++) {
				if (i == x[k]) {
					skeep = 1;
					break;
			    }
		    }
		    if (skeep == 1) continue;
	  	    if (g->scclist[i] > max) {
				max = g->scclist[i];
		        x[j] = i;
		    }
        }
    }

    for (i=0; i<5; i++)
        printf("scclist[%d]=%d, count is %d\n", x[i], g->scclist[x[i]], g->nscc);
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    for (i=0; i<5; i++)
        printf("%d,", g->scclist[x[i]]);
    printf("\n");
    printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}

printlead(graph *g)
{
	int i;

	for (i=0; i<g->n; i++) {
        printf("leader[%d]=%d\n", i+1, g->f[i]);
        if (i > 20) break;
    }
}

int initg(graph *g)
{
	int i;           /* counter */
	int status;

    status = TRUE;

    g->v  = malloc(NMAX*sizeof(struct vertex *));
    g->ex = malloc(NMAX*sizeof(int));
    g->stack = malloc(NMAX*sizeof(int));
    g->f  = malloc(NMAX*sizeof(int));
    g->scclist  = malloc(NMAX*sizeof(int));
	g->n = 0;
	g->m = 0;
	g->directed = 0;
	g->stp = -1;
	g->nscc = 0;

	for (i=0; i < NMAX; i++) {
		g->f[i] = 0;            /* process order     */
		g->ex[i] = UNEX;        /* explored vertex   */
		g->stack[i] = 0;        /* proces stack      */
	    g->v[i] = NULL;         /* vertex pointer    */
	    g->scclist[i] = 0;      /* SCC list          */
    }
    if (g->v == NULL || g->ex == NULL || g->stack == NULL || g->f == NULL) return (FALSE);
    return (TRUE);
}

#define MAXLINE 30

int readg(char *file, graph *g, graph *gx, int inverse)
{
    char str[MAXLINE];
    char delims[] = " \n";
    char *temp;
    int i1, i2, i3;
    vertex *p, *q;
    FILE *in;
    int status;

    status = TRUE;
    in= fopen(file, "r");
    while (fgets(str,MAXLINE,in) != NULL) {
		temp = (char *) strtok( str, delims );
		if (temp == NULL) { printf ("ERROR readg token #1\n"); fclose(in); break; }
        i1 = atoi(temp);
		if (temp == NULL) { printf ("ERROR readg token #2\n"); fclose(in); break; }
		temp = (char *) strtok( NULL, delims );
        i2 = atoi(temp);
        if (inverse == TRUE) {
			i3 = i1;
			i1 = i2;
			i2 = i3;
	    }
	    else {
	        i1 = gx->f[i1-1];
	        i2 = gx->f[i2-1];
	    }
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
	fclose(in);
	return (status);
}

DFS(graph *g, int s, int phase)  /* Depth First Search (LIFO) */
{
	vertex *p, *q;
	int ip, iq, stat;
    int xscc;

	if (debug == TRUE) printf("phase %d ??????????????? DFS STACK POINTER %d\n", phase, g->stp);

    xscc = 0;
    if (s < 1 || s > g->n) return;               /* all nodes initially unexplored */
	g->ex[s-1] = EXPL;                           /* mark s as explored  */
	explored++;
    g->stack[++(g->stp)] = s;                                /* initialize LIFO with s */
    if (phase == 2) xscc++;               /* increment scc counter for this DFS call */
	while (g->stp >= 0) {                           /* while LIFO not empty */
		ip = g->stack[(g->stp)];                     /* read from stack at pointer stp, do not decrement */
		if (g->ex[ip-1] == PROC) {
			g->stp--;
			continue;
	    }
        if (debug == TRUE) printf("DFS vertex stack=%d  id=%d [%d]\n", g->stp, g->v[ip-1]->vid, ip-1);
		p = g->v[ip-1];
		if (p == NULL) {
			printf ("ERROR (ip=%d)\n",ip);
			return;
	    }
		q = (vertex *) p->next;
		stat = FALSE;
	    while (q != NULL) {                      /* for each edge (p,q) */
		    if (debug == TRUE) printf("+++ vertex %d \n",q->vid);
            iq = q->vid;
		    if (g->ex[iq-1] == UNEX) {
				stat = TRUE;                        /* there is at least one edge found to continue */
				explored++;
				g->ex[iq-1] = EXPL;                 /* if q unexplored, mark it */
                g->stack[++(g->stp)] = iq;          /* add q to LIFO */
                if (phase == 2) xscc++;               /* increment scc counter for this DFS call */
		    }
		    q = (vertex *) q->next;
	    }
	    if (stat == FALSE) {          /* end of route */
	        g->ex[ip-1] = PROC;
	        if (phase == 2) g->f[ip-1] = leader;             /* SCC leader in 2nd pass    */
	        if (phase == 1) g->f[ip-1] = ++fintime;          /* finished time in 1st pass */
		    if (debug == TRUE) printf(" ################# finish(%d)=%d\n",ip,g->f[ip-1]);
	    }
    }
    if (phase == 2) g->scclist[g->nscc++] = xscc;
}

DFSloop(graph *g, int pass)
{
	int i;

    fintime = 0;
    leader = 0;
    explored = 0;
    count = 0;
    for (i = g->n; i >= 1; i--) {
		if (g->ex[i-1] == PROC) continue;
        if (debug == TRUE) printf("running DFS (pass %d) ... for i=%d\n", pass, i);
        leader = i;
        DFS(g,i, pass);
	    if (debug == TRUE) printf("finished DFS (pass %d) ... for i=%d\n", pass, i);
	    if (debug == TRUE) printf(" n=%d m=%d explored=%d\n", g->n, g->m, explored);
        count++;
	}
}

void main(int argc, char *argv[])
{
    graph g, ginv;
    int stat;

    debug = FALSE;
    if (argc < 2) { printf("%s: missing file name"); exit; }
    if (argc == 3 && argv[2][0] == 'D') debug = TRUE;

    stat = initg(&ginv);
    if (stat == FALSE) { printf("initg: malloc error. exit"); exit; }
    stat = readg(argv[1], &ginv, NULL, TRUE);
    if (stat == FALSE) { printf("readg: data error. exit"); exit; }
    if (debug == TRUE) printg(&ginv);
	printf("----------------------------------\n");
    printf("INVERSE GRAPH n=%d m=%d\n",ginv.n,ginv.m);
	printf("----------------------------------\n");

	printf("--------------------------------------------\n");
    printf("running DFS-loop pass 1 (inverse graph) ... \n");
	printf("--------------------------------------------\n");
    DFSloop(&ginv, 1);
	printf("--------------------------------------------\n");
	printf(" n=%d m=%d explored=%d\n", ginv.n, ginv.m, countg(&ginv));
	printf("connected components=%d\n",count);
    printf("--------------------------------------------\n");

    stat = initg(&g);
    if (stat == FALSE) { printf("initg: malloc error. exit"); exit; }
    stat = readg(argv[1], &g, &ginv, FALSE);
    if (stat == FALSE) { printf("readg: data error. exit"); exit; }
    if (debug == TRUE) printg(&g);
	printf("----------------------------------\n");
    printf("INPUT GRAPH   n=%d m=%d\n",g.n,g.m);
	printf("----------------------------------\n");

	printf("--------------------------------------------\n");
    printf("running DFS-loop pass 2 (original graph) ...\n");
	printf("--------------------------------------------\n");
    DFSloop(&g, 2);
	printf("--------------------------------------------\n");
	printf(" n=%d m=%d explored=%d\n", g.n, g.m, countg(&g));
	printf("connected components=%d\n",count);
    printf("--------------------------------------------\n");
    qsort(g.scclist,g.nscc,sizeof(int), intcompare);
    printscc(&g);
    printlead(&g);
}