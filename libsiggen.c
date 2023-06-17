#include <math.h>
#include "libsiggen.h"
void generate_saw(float *re, float *im, const unsigned int N)
{
    for (unsigned int i = 0; i < N; i++)
    {
        re[i] = i;
        im[i] = -i + N;
    }
}

void generate_square(float *re, float *im, const unsigned int N)
{
    const unsigned int N_2 = N / 2;
    for (unsigned int i = 0; i < N; i++)
    {
        re[i] = i / N_2;
        im[i] = 1 - (i / N_2);
    }
}
void generate_triangle(float *re, float *im, const unsigned int N)
{
    const unsigned int N_2 = N / 2;
    for (unsigned int i = 0; i < N; i++)
    {
        if (i < N_2)
        {
            re[i] = i;
            im[i] = -i + N_2;
        }
        else
        {
            re[i] = i - N_2;
            im[i] = -i + N;
        }
    }
}
void generate_sin(float *re, float *im, const unsigned int N)
{
    const float pi = -3.14159265358979323846;
    for (unsigned int i = 0; i < N; i++)
    {

        float ang = pi * (float)i / (float)N;
        re[i] = sin(ang);
        im[i] = cos(ang);
    }
}