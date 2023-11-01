#include <stdio.h>
#include <string.h>

#define MATCH  0        /* enumerated type symbol for match  */
#define INSERT 1        /* enumerated type symbol for insert */
#define DELETE 2        /* enumerated type symbol for delete */

#define MAXLEN 100

typedef struct {
	int cost;                   /* cost of reaching this cell */
	int parent;                 /* parent cell                */
} cell;

cell m[MAXLEN+1][MAXLEN+1];     /* dynamic programming table  */

int opt;

goal_cell(char *s, char *t, int *i, int *j)
{
	int k;            /* counter */

    if (opt == 1) {
	    *i = strlen(s) - 1;
	    *j = 0;
	    for (k=1; k<=strlen(t); k++)
	        if (m[*i][k].cost < m[*i][*j].cost) *j = k;
	}
	else {
	    *i = strlen(s) - 1;
	    *j = strlen(t) - 1;
    }
}

int match(char c, char d)
{
	int val = 1;
	if (opt == 2) val = MAXLEN;
	if (c == d) return(0);
	else return(val);
}

int indel(char c)
{
	return(1);
}

print_matrix(char *s, char *t, int k)
{
	int ii, jj;

	for (jj=0; jj<=strlen(t); jj++)
	    printf("%c ", t[jj]);
	printf("\n");
	for (ii=0; ii<=strlen(s); ii++) {
		printf("%c ", s[ii]);
	    for (jj=0; jj<=strlen(t); jj++) {
	        if (k == 0) printf ("%2d ", m[ii][jj].cost);
	        if (k == 1) printf ("%2d ", m[ii][jj].parent);
	    }
	    printf("\n");
	}
}

row_init(int i)
{
	if (opt == 1) {
	    m[0][i].cost = 0;
	    m[0][i].parent = -1;
    }
    else {
	    m[0][i].cost = i;
	    if (i>0)
	        m[0][i].parent = INSERT;
	    else
	        m[0][i].parent = -1;
	}
}

column_init(int i)
{
	m[i][0].cost = i;
	if (i>0)
	    m[i][0].parent = DELETE;
	else
	    m[i][0].parent = -1;
}

int string_compare (char *s, char *t)
{
	int i, j, k;         /* counters */
	int opt[3];          /* cost of the tree options */

	for (i=0; i<MAXLEN; i++) {
		row_init(i);
		column_init(i);
	}

	for (i=1; i<strlen(s); i++) {
		for (j=1; j<strlen(t); j++) {
			opt[MATCH] = m[i-1][j-1].cost + match(s[i], t[j]);
			opt[INSERT] = m[i][j-1].cost + indel(t[j]);
			opt[DELETE] = m[i-1][j].cost + indel(s[i]);

			m[i][j].cost = opt[MATCH];
			m[i][j].parent = MATCH;
			for (k=INSERT; k<=DELETE; k++)
			    if (opt[k] < m[i][j].cost) {
					 m[i][j].cost = opt[k];
					 m[i][j].parent = k;
				 }
			 }
    }
    goal_cell(s,t,&i,&j);
    return( m[i][j].cost );
}

insert_out(char *t, int j)
{
	printf("I");
}

delete_out(char *s, int i)
{
	printf("D");
}

match_out(char *s, char *t, int i, int j)
{
	if (s[i] == t[j]) printf("M");
	else printf("S");
}

reconstruct_path(char *s, char *t, int i, int j)
{
	if(m[i][j].parent == -1) return;

    if (m[i][j].parent == MATCH) {
		reconstruct_path(s,t,i-1,j-1);
		match_out(s,t,i,j);
		return;
	}

    if (m[i][j].parent == INSERT) {
		reconstruct_path(s,t,i,j-1);
		insert_out(t,j);
		return;
	}

    if (m[i][j].parent == DELETE) {
		reconstruct_path(s,t,i-1,j);
		delete_out(s,i);
		return;
	}
}


main(int argc, char *argv[])
{
     int i;
	 char s[MAXLEN],t[MAXLEN];		/* input strings */

     opt=0;
	 s[0] = t[0] = ' ';
	 sscanf(argv[1], "%d",&opt);
	 sscanf(argv[2], "%s",&(s[1]));
	 sscanf(argv[3], "%s",&(t[1]));

     i = string_compare(s, t);
     printf("string1=%s= %d\n", s, strlen(s));
     printf("string2=%s= %d\n", t, strlen(t));
     printf("cost=%d\n", i);
     reconstruct_path(s, t, strlen(s), strlen(t));
     printf("\n");
     printf("------------- cost -----------\n");
     print_matrix(s,t,0);
     printf("------------- parent ---------\n");
     print_matrix(s,t,1);
}

