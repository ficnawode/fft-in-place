#include <stdio.h>
#include <string.h>
#include "libfft.h"
#include "libsiggen.h"

static void __write_complex_to_file(const float complex *buffer, const uint16_t N, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    fprintf(fp, "re,im\n");
    for (uint16_t i = 0; i < N; i++)
    {
        fprintf(fp, "%f, %f\n", crealf(buffer[i]), cimagf(buffer[i]));
    }
    fclose(fp);
}

static void __run_fft(float complex *buffer, const uint16_t N, const char *name)
{
    char filenamebuffer[50];
    sprintf(filenamebuffer, "%s_original.csv", name);
    __write_complex_to_file(buffer, N, filenamebuffer);

    fft(buffer, N);

    sprintf(filenamebuffer, "%s.csv", name);
    __write_complex_to_file(buffer, N, filenamebuffer);
}

int main()
{
    const uint16_t MAX_N = 1024;
    float complex buffer[MAX_N];

    generate_saw(buffer, MAX_N);
    __run_fft(buffer, MAX_N, "saw");

    generate_square(buffer, MAX_N);
    __run_fft(buffer, MAX_N, "square");

    generate_triangle(buffer, MAX_N);
    __run_fft(buffer, MAX_N, "triangle");

    generate_sin(buffer, MAX_N);
    __run_fft(buffer, MAX_N, "sin");

    return 0;
}