#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include"rw_bmp.h"
#include"gray.h"

int main()
{
    char *path = "Lena_512512.bmp";
    char *path_gray_max = "Lena_512512_gray_max.bmp";
    char *path_gray_mean = "Lena_512512_gray_mean.bmp";
    char *path_gray_weight = "Lena_512512_gray_weight.bmp";
    bmp bitp = {.pBmpBuf = NULL};
    bitp = readbmp(path);
    bmp gray_max = gray(bitp, 0);
    bmp gray_mean = gray(bitp, 1);
    bmp gray_weight = gray(bitp, 2);
    writebmp(path_gray_max, gray_max);
    writebmp(path_gray_mean, gray_mean);
    writebmp(path_gray_weight, gray_weight);
    free_bmp(gray_max);
    free_bmp(gray_mean);
    free_bmp(gray_weight);
    return 0;
}
