#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXINT INT_MAX
typedef int bool;
#define TRUE 1
#define FALSE 0

#define MAXJOBS 100000   /* maximum number of jobs */

typedef int (*compfn)(const void*, const void*);


typedef struct {
	int weight;          /* job weight                 */
	int length;          /* job length                 */
	int wtdiff;          /* weight - length            */
	float wtratio;       /* weight/length              */
} job;

int compare_diff(job **, job **);
int compare_ratio(job **, job **);

typedef struct {
	job **list;    /* start of job list          */
	int njobs;     /* number of jobs             */
    double wct;      /* weighted completition time */
    double ct;       /* completition time          */
} schedule ;

int compare_diff(job **i, job **j)
{
/*	printf("compare_diff: %d %d\n", (*i)->wtdiff, (*j)->wtdiff);  */
	if ((*i)->wtdiff < (*j)->wtdiff) return(1);
	if ((*i)->wtdiff > (*j)->wtdiff) return(-1);
	if ((*i)->wtdiff == (*j)->wtdiff) {
		if ((*i)->weight < (*j)->weight) return(1);
		if ((*i)->weight > (*j)->weight) return(-1);
		return(0);
	}
}

int compare_ratio(job **i, job **j)
{
/*	printf("compare_diff: %f %f\n", (*i)->wtratio, (*j)->wtratio);  */
	if ((*i)->wtratio < (*j)->wtratio) return(1);
	if ((*i)->wtratio > (*j)->wtratio) return(-1);
	return(0);
}

init_jobs(schedule *j)
{
	j->njobs = 0;
	j->wct = 0;
	j->ct = 0;
}


read_jobs(schedule *j)
{
	int i;               /* counter */
	int nu;              /* number of jobs */
	int we, le;          /* weight lenght */

	scanf("%d",&nu);
	j->list = malloc(sizeof(job *)*nu);

    j->njobs = nu;
	j->wct = 0;
	j->ct = 0;

	for (i=0; i<j->njobs; i++) {
	     scanf("%d %d",&we,&le);
	     j->list[i] = malloc(sizeof(job));
	     j->list[i]->weight = we;
	     j->list[i]->length = le;
	     j->list[i]->wtdiff = we - le;
	     j->list[i]->wtratio = (float) we / (float) le;
    }
}


print_jobs(schedule *j)
{
	int i;          /* counter */
    printf("%d\n", j->njobs);
	for (i=0; i<j->njobs; i++) {
		printf("%d %d %d %f\n", j->list[i]->weight, j->list[i]->length, j->list[i]->wtdiff, j->list[i]->wtratio);
    }
}

queue_jobs(schedule *j)
{
	int i;          /* counter */

	j->wct = 0.0;
	j->ct = 0.0;

    for (i=0; i<j->njobs; i++) {
        j->ct = (double)j->list[i]->length + j->ct;
        j->wct = (double)j->list[i]->weight * j->ct + j->wct;
/*		printf("%d %d %d %f %f %f\n", j->list[i]->weight, j->list[i]->length, j->list[i]->wtdiff, j->list[i]->wtratio, j->ct, j->wct);  */
    }
    printf("WEIGHTED SUM %20.0f\n", j->wct);
}

sort_jobs(schedule *s, int mode)
{
	if (mode == 0)
        qsort((void *)s->list,s->njobs,sizeof(job *), (compfn)compare_diff);
    else
        qsort((void *)s->list,s->njobs,sizeof(job *), (compfn)compare_ratio);
}

main(int argc, char *argv[])
{
	schedule s;

    int mode = -1;

    if (argc > 1) {
        if (argv[1][0] == '0') mode = 0;
        if (argv[1][0] == '1') mode = 1;
    }

    printf("READ JOBS\n");
	read_jobs(&s);
/*  printf("PRINT JOBS\n");
	print_jobs(&s);  */
    if (mode >= 0) {
        printf("SORT JOBS %d\n", mode);
    	sort_jobs(&s, mode);
 /*       printf("PRINT JOBS\n");
    	print_jobs(&s);   */
        printf("QUEUE JOBS\n");
    	queue_jobs(&s);
    }
    printf("END JOBS\n");
}

