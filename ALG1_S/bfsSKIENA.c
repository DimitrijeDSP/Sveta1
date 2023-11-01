#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define TRUE 1
#define FALSE 0

#define MAXV 1000    /* maximum number of vertices */

bool processed[MAXV+1];         /* which vertices have been processed */
bool discovered[MAXV+1];        /* which vertices have been found */
int parent[MAXV+1];             /* discovery relation */
int color[MAXV+1];              /* coloring information */
bool bipartite;

#define BLACK 100
#define WHITE 200
#define UNCOLORED 300

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

#define QUEUESIZE       1000

typedef struct {
        int q[QUEUESIZE+1];		/* body of queue */
        int first;              /* position of first element */
        int last;               /* position of last element */
        int count;              /* number of queue elements */
} queue;

#define DEBUG 0

init_queue(queue *q)
{
        q->first = 0;
        q->last = QUEUESIZE-1;
        q->count = 0;
}

enqueue(queue *q, int x)
{
        if (q->count >= QUEUESIZE)
		printf("Warning: queue overflow enqueue x=%d\n",x);
        else {
                q->last = (q->last+1) % QUEUESIZE;
                q->q[ q->last ] = x;
                q->count = q->count + 1;
        }
}

int dequeue(queue *q)
{
        int x;

        if (q->count <= 0) printf("Warning: empty queue dequeue.\n");
        else {
                x = q->q[ q->first ];
                q->first = (q->first+1) % QUEUESIZE;
                q->count = q->count - 1;
        }

        return(x);
}

int empty_queue(queue *q)
{
        if (q->count <= 0) return (TRUE);
        else return (FALSE);
}

print_queue(queue *q)
{
        int i,j;

        i=q->first;

        printf("QUEUE: (%d,%d) ", q->first,q->last);
        while (i != q->last) {
                printf("%c ",q->q[i]);
                i = (i+1) % QUEUESIZE;
        }

        printf("%2d ",q->q[i]);
        printf("\n");
}

initialize_graph(graph *g, bool directed)
{
	int i;           /* counter */

	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;

	for (i=1; i<=MAXV; i++) g->degree[i] = 0;
	for (i=1; i<=MAXV; i++) g->edges[i] = NULL;
}

read_graph(graph *g, bool directed)
{
	int i;                /* counter */
	int m;                /* number of edges */
	int x, y;             /* vertices in edge (x,y) */

	initialize_graph(g, directed);

	scanf("%d %d",&(g->nvertices),&m);

	for (i=1; i<=m; i++) {
	     scanf("%d %d",&x,&y);
	     insert_edge(g,x,y,directed);
    }
}

insert_edge(graph *g, int x, int y, bool directed)
{
	edgenode *p;                    /* temporary pointer */

	p = malloc(sizeof(edgenode));   /* allocate edgenode storage */

	p->weight = NULL;
	p->y = y;
	p->next = g->edges[x];

	g->edges[x] = p;                /* insert at head of list */
	g->degree[x] ++;

	if (directed == FALSE)
	    insert_edge(g,y,x,TRUE);
	else
	    g->nedges ++;
}


print_graph(graph *g)
{
	int i;            /* counter */
	edgenode *p;      /* temporary pointer */

	for (i=1; i<=g->nvertices; i++) {
	    printf("%d ", i);
	    p = g->edges[i];
	    while (p != NULL) {
			printf(" %d", p->y);
			p = p->next;
	    }
	    printf("\n");
    }
}

initialize_search(graph *g)
{
	int i;               /* counter */

	for (i=1; i<=g->nvertices; i++) {
		processed[i] = discovered[i] = FALSE;
		parent[i] = -1;
    }
}


bfs(graph *g, int start)     /* BREADTH-FIRST SEARCH */
{
	queue q;                 /* queue of vertices to visit */
	int v;                   /* current vertex */
	int y;                   /* successor vertex */
	edgenode *p;             /* temporary pointer */

	init_queue(&q);
	enqueue(&q, start);
	discovered[start] = TRUE;

    while(empty_queue(&q) == FALSE) {
	    if (DEBUG == 1) print_queue(&q);
		v = dequeue(&q);
		process_vertex_early(v);
		processed[v] = TRUE;
		p = g->edges[v];

        while(p != NULL) {
			y = p->y;
			if (processed[y] == FALSE || g->directed == TRUE)
			    process_edge_tc(v,y);
			if (discovered[y] == FALSE) {
				 enqueue(&q, y);
				 discovered[y] = TRUE;
                 parent[y] = v;
		    }
            p = p->next;
		}
		process_vertex_late(v);
	}
}

process_vertex_late(int v)
{
}

process_vertex_early(int v)
{
	printf("processed vertex %d\n",v);
}

process_edge(int x, int y)
{
	printf("processed edge (%d, %d)\n",x,y);
}

process_edge_tc(int x, int y)
{
	if (color[x] == color[y]) {
		bipartite = FALSE;
		printf("Warning: not bipartite due to (%d,%d)\n", x, y);
	}
	color[y] = complement(color[x]);
	printf("processed edge (%d, %d)\n",x,y);
}

complement(int color)
{
	if (color == WHITE) return(BLACK);
	if (color == BLACK) return(WHITE);
    return(UNCOLORED);
}

find_path(int start, int end, int parents[])
{
	if ((start == end) || (end == -1))
	     printf("\n%d",start);
	else {
		find_path(start,parents[end], parents);
		printf(" %d", end);
    }
}

connected_components(graph *g)
{
	int c;              /* component number */
	int i;              /* counter */

	c = 0;
	for (i=1; i<=g->nvertices; i++)
	    if (discovered[i] == FALSE) {
			c = c+1;
			printf("\n############ Component %d:\n",c);
			bfs(g,i);
			printf("\n");
		}
}

two_color(graph *g)
{
	int i;              /* counter */

    for (i=1; i<=(g->nvertices); i++)
        color[i] = UNCOLORED;

    bipartite = TRUE;

	for (i=1; i<=g->nvertices; i++)
	    if (discovered[i] == FALSE) {
			color[i] = WHITE;
			bfs(g,i);
		}
}

print_color(graph *g)
{
	int i;              /* counter */

    for (i=1; i<=(g->nvertices); i++)
        printf("color[%d]=%d\n", i, color[i]);
}

main(int argc, char *argv[])
{
	graph g;
    int i, ix;
	bool bx;    /* bx - directed or undirected */

	printf("=============== BFS graph type =================\n");
	scanf("%d",&ix);
	bx = FALSE;
	if (ix == 1) bx = TRUE;
	if (bx == TRUE)  printf("DIRECTED GRAPH\n"); else printf("UNDIRECTED GRAPH\n");

	printf("============== adjancency list =================\n");
	read_graph(&g, bx);
	print_graph(&g);

	printf("============== connected components =================\n");
    initialize_search(&g);
    connected_components(&g);

	printf("================ parent ===================\n");
    initialize_search(&g);
    bfs(&g, 1);
    printf("########### PARENT: ");
	for (i=1; i<=g.nvertices; i++)
		printf(" %d",parent[i]);
	printf("\n");

	printf("=============== find path ==================\n");
    initialize_search(&g);
    bfs(&g, 1);
    printf ("############### VERTEX PATH \n");
	for (i=1; i<=g.nvertices; i++)
		find_path(1,i,parent);
	printf("\n");

	printf("================== two color =====================\n");
    initialize_search(&g);
    two_color(&g);
    print_color(&g);
}

