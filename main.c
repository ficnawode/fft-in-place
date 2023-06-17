#include <stdio.h>
#include <string.h>
#include "libfft.h"
#include "libsiggen.h"

static void __write_complex_to_file(const float *re, const float *im, const unsigned int N, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    fprintf(fp, "re,im\n");
    for (unsigned int i = 0; i < N; i++)
    {
        fprintf(fp, "%f, %f\n", re[i], im[i]);
    }
    fclose(fp);
}

static void __run_fft(float *re, float *im, const unsigned int N, const char *name)
{
    char filenamebuffer[50];
    sprintf(filenamebuffer, "%s_original.csv", name);
    __write_complex_to_file(re, im, N, filenamebuffer);

    fft(re, im, N);

    sprintf(filenamebuffer, "%s.csv", name);
    __write_complex_to_file(re, im, N, filenamebuffer);
}

int main()
{
    const unsigned int MAX_N = 1024;
    float re[MAX_N];
    float im[MAX_N];

    generate_saw(re, im, MAX_N);
    __run_fft(re, im, MAX_N, "saw");

    generate_square(re, im, MAX_N);
    __run_fft(re, im, MAX_N, "square");

    generate_triangle(re, im, MAX_N);
    __run_fft(re, im, MAX_N, "triangle");

    generate_sin(re, im, MAX_N);
    __run_fft(re, im, MAX_N, "sin");

    return 0;
}