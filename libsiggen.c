#include <math.h>
#include "libsiggen.h"

void generate_saw(float complex *buffer, const uint16_t N)
{
    for (uint16_t i = 0; i < N; i++)
    {
        buffer[i] = i / (float)N + I * (-i + N) / (float)N;
    }
}

void generate_square(float complex *buffer, const uint16_t N)
{
    const uint16_t N_2 = N / 2;
    for (uint16_t i = 0; i < N; i++)
    {
        buffer[i] = i + I * (N_2 - i);
        buffer[i] /= (float)N_2;
    }
}

void generate_triangle(float complex *buffer, const uint16_t N)
{
    const uint16_t N_2 = N / 2;
    for (uint16_t i = 0; i < N; i++)
    {
        if (i < N_2)
        {
            buffer[i] = i + I * (N_2 - i);
        }
        else
        {
            buffer[i] = N - i + I * (i - N_2);
        }
        buffer[i] /= (float)N_2;
    }
}

void generate_sin(float complex *buffer, const uint16_t N)
{
    const float pi = -3.14159265358979323846;
    for (uint16_t i = 0; i < N; i++)
    {
        float ang = 2 * pi * (float)i / (float)N;
        buffer[i] = sin(ang) + I * cos(ang);
    }
}