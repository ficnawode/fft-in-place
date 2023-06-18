#include <math.h>
#include "libfft.h"

static inline void __apply_mask(uint16_t *target, uint16_t mask)
{
    while (*target & (mask >>= 1))
        *target &= ~mask;
    *target |= mask;
}

static inline void __try_swap_elements(float complex *buffer, const uint16_t target, const uint16_t position)
{
    if (target > position)
    {
        const float complex temp = buffer[target];
        buffer[target] = buffer[position];
        buffer[position] = temp;
    }
}

static void __rearrange(float complex *buffer, const uint16_t N)
{
    uint16_t target = 0;
    for (uint16_t position = 0; position < N; position++)
    {
        __try_swap_elements(buffer, target, position);
        __apply_mask(&target, N);
    }
}

static inline void __iterate_pairs(float complex *buffer, const float complex twiddle, uint16_t pair, const uint16_t step, const uint16_t N)
{
    const uint16_t jump = step << 1;
    for (; pair < N; pair += jump)
    {
        const uint16_t match = pair + step;
        const float complex product = twiddle * buffer[match];
        buffer[match] = buffer[pair] - product;
        buffer[pair] += product;
    }
}

static inline void __iterate_groups(float complex *buffer, const uint16_t step, const uint16_t N)
{
    const float pi = -3.14159265358979323846;
    float complex twiddle = 1.0 + 0.0 * I;
    for (uint16_t group = 0; group < step; group++)
    {
        __iterate_pairs(buffer, twiddle, group, step, N);
        if (group + 1 == step)
        {
            continue;
        }

        float angle = pi * ((float)group + 1) / (float)step;
        twiddle = cos(angle) + I * sin(angle);
    }
}

static void __compute(float complex *buffer, const uint16_t N)
{

    for (uint16_t step = 1; step < N; step <<= 1)
    {
        __iterate_groups(buffer, step, N);
    }
}

void fft(float complex *buffer, const uint16_t N)
{
    __rearrange(buffer, N);
    __compute(buffer, N);
}