#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 60
void main(int argc, char *argv[])
{
	int *label;
    char str[MAXLINE];
    char delims[] = " \n";
    char *temp;
    int i1, i2, i3, maxel, stat, ix1, ix2, i, counter, sig1, sig2;
    FILE *in;
    int status;

    in= fopen(argv[1], "r");

    fgets(str,MAXLINE,in);
	maxel = atoi((char *)strtok( str, delims ));

    label = (int *) malloc(sizeof(int)*(maxel+2));

    for (i=0; i<maxel; i++) {
		label[i] = 0;
    }
    counter = 1;
    while (fgets(str,MAXLINE,in) != NULL) {
		temp = (char *) strtok( str, delims );
        ix1 = atoi(temp);
		temp = (char *) strtok( NULL, delims );
        ix2 = atoi(temp);
        sig1 = 1;
        sig2 = 1;
        if (ix1 < 0) sig1 = -1;
        if (ix2 < 0) sig2 = -1;
        if (label[sig1*ix1] == 0) label[sig1*ix1] = counter++;
        if (label[sig2*ix2] == 0) label[sig2*ix2] = counter++;
	}
	fclose(in);

    in= fopen(argv[1], "r");

    fgets(str,MAXLINE,in);
	maxel = atoi((char *)strtok( str, delims ));
    printf("%d\n", counter-1);

    while (fgets(str,MAXLINE,in) != NULL) {
		temp = (char *) strtok( str, delims );
        ix1 = atoi(temp);
		temp = (char *) strtok( NULL, delims );
        ix2 = atoi(temp);
        sig1 = 1;
        sig2 = 1;
        if (ix1 < 0) sig1 = -1;
        if (ix2 < 0) sig2 = -1;
        printf("%d %d\n", sig1*label[sig1*ix1], sig2*label[sig2*ix2]);
	}
	fclose(in);
}

