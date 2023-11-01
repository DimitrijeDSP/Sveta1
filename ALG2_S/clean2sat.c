#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 60
void main(int argc, char *argv[])
{
	int *plus, *minus;
    char str[MAXLINE];
    char delims[] = " \n";
    char *temp;
    int i1, i2, i3, maxel, stat, ix1, ix2, i;
    FILE *in;
    int status;

    in= fopen(argv[1], "r");

    fgets(str,MAXLINE,in);
	maxel = atoi((char *)strtok( str, delims ));

    plus = (int *) malloc(sizeof(int)*(maxel+2));
    minus = (int *) malloc(sizeof(int)*(maxel+2));

    for (i=0; i<maxel; i++) {
		plus[i] = 0;
		minus[i] = 0;
    }
    while (fgets(str,MAXLINE,in) != NULL) {
		temp = (char *) strtok( str, delims );
        ix1 = atoi(temp);
		temp = (char *) strtok( NULL, delims );
        ix2 = atoi(temp);
        if (ix1 < 0) minus[-1*ix1]++;
        if (ix1 > 0) plus[ix1]++;
        if (ix2 < 0) minus[-1*ix2]++;
        if (ix2 > 0) plus[ix2]++;
	}
	fclose(in);

    in= fopen(argv[1], "r");

    fgets(str,MAXLINE,in);
	maxel = atoi((char *)strtok( str, delims ));
    printf("%d\n", maxel);

    while (fgets(str,MAXLINE,in) != NULL) {
		temp = (char *) strtok( str, delims );
        ix1 = atoi(temp);
		temp = (char *) strtok( NULL, delims );
        ix2 = atoi(temp);
        if (ix1 < 0 && plus[-1*ix1] == 0) continue;
        if (ix1 > 0 && minus[ix1] == 0) continue;
        if (ix2 < 0 && plus[-1*ix2] == 0) continue;
        if (ix2 > 0 && minus[ix2] == 0) continue;
        printf("%d %d\n", ix1, ix2);
	}
	fclose(in);

}

