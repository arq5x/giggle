#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <stdint.h>

/* calculate the list of bins that may overlap with region [beg,end) (zero-based) */
#define MAX_BIN (((1<<18)-1)/7)
int reg2bins(int beg, int end, uint16_t list[MAX_BIN])
{
    int i = 0, k;
    --end;
    list[i++] = 0;
    for (k = 1 + (beg>>26); k <= 1 + (end>>26); ++k) list[i++] = k;
    for (k = 9 + (beg>>23); k <= 9 + (end>>23); ++k) list[i++] = k;
    for (k = 73 + (beg>>20); k <= 73 + (end>>20); ++k) list[i++] = k;
    for (k = 585 + (beg>>17); k <= 585 + (end>>17); ++k) list[i++] = k;
    for (k = 4681 + (beg>>14); k <= 4681 + (end>>14); ++k) list[i++] = k;
    return i;
}

int main(int argc, char **argv)
{
    if (argc != 3)
        errx(1,"usage:\t%s <start> <end>\n", argv[0]);

    int beg = atoi(argv[1]);
    int end = atoi(argv[2]);
    uint16_t *list = (uint16_t *)calloc(MAX_BIN, sizeof(uint16_t));

    int num_bins = reg2bins(beg, end, list);

    //printf("%s\t%d\t%d\t", chrm, beg, end);

    int i;
    for (i = 0; i < num_bins; ++i) {
        if (i != 0)
            printf(",");
        printf("%d", list[i]);
    }

    printf("\n");
}
