#include <stdio.h>
#include <stdlib.h>

int mask_2bit(int n, unsigned int *mask, int mode)
{
    int i, j, k, y, xx, *x, cnt, nobits;
    unsigned int bbb;

    x = (int *) malloc(sizeof(int)*n);

    for (k=0; k<n; k++) {
        x[k] = 0;
	}

    cnt = 0;
    for (i=0; i<n; i++) {
        for (j=0; j<=i; j++) {
            nobits=0;
	        bbb = 0;
            if (x[i] == 0) y = 1;
            if (x[i] == 1) y = 0;
            if (x[j] == 0) y = 1;
            if (x[j] == 1) y = 0;
            for (k=0; k<n; k++) {
  	            if (k == i || k == j)
                    xx = y;
                else
                    xx = x[k];
                if (xx == 1) nobits++;
                printf("%d ", xx);
                bbb |= ((xx == 1) << n-k-1);
            }
            printf("\nbbb=%d\n", bbb);
            if (mode == 0)
                mask[cnt++] = bbb;
            else
                mask[cnt++] = nobits;
        }
    }
    return (cnt);
}

main(int arg, char *argv[])
{
    int cnt, i;
    unsigned int mask[400];

    cnt = mask_2bit(24, mask,0);

    for (i=0; i<cnt; i++) {
		printf("%d: %d\n", i, mask[i]);
	}
}

