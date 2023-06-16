#include <stdio.h>
#include "libfft.h"

#define MAX_N 2048

int main()
{
    float x_re[MAX_N];
    float x_im[MAX_N];
    float x_re_original[MAX_N];
    float x_im_original[MAX_N];
    for (int i = 0; i < MAX_N; i++)
    {
        x_re[i] = i % (MAX_N / 2);
        x_im[i] = i % (MAX_N / 2);
        x_re_original[i] = x_re[i];
        x_im_original[i] = x_im[i];
    }

    fft(x_re, x_im, MAX_N);
    FILE *x_fp = fopen("x.csv", "w");
    FILE *x_orig_fp = fopen("x_original.csv", "w");
    fprintf(x_fp, "re, im\n");
    fprintf(x_orig_fp, "re, im\n");

    for (int i = 0; i < MAX_N; i++)
    {
        fprintf(x_fp, "%f, %f\n", x_re[i], x_im[i]);
        fprintf(x_orig_fp, "%f, %f\n", x_re_original[i], x_im_original[i]);
    }
    fclose(x_fp);
    fclose(x_orig_fp);
    return 0;
}