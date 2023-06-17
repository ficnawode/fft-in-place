#include <math.h>

static inline void __apply_mask(unsigned int *target, unsigned int mask)
{
    while (*target & (mask >>= 1))
        *target &= ~mask;
    *target |= mask;
}

static inline void __try_swap_elements(float *re, float *im, const unsigned int target, const unsigned int position)
{
    if (target > position)
    {
        const float temp_re = re[target];
        const float temp_im = im[target];
        re[target] = re[position];
        im[target] = im[position];
        re[position] = temp_re;
        im[position] = temp_im;
    }
}

static void __rearrange(float *re, float *im, const unsigned int N)
{
    unsigned int target = 0;
    for (unsigned int position = 0; position < N; position++)
    {
        __try_swap_elements(re, im, target, position);
        __apply_mask(&target, N);
    }
}

static inline void __iterate_pairs(float *re, float *im, unsigned int pair, const unsigned int step, const unsigned int N, const float twiddle_re, const float twiddle_im)
{
    const unsigned int jump = step << 1;
    for (; pair < N; pair += jump)
    {
        const unsigned int match = pair + step;
        const float product_re = twiddle_re * re[match] - twiddle_im * im[match];
        const float product_im = twiddle_im * re[match] + twiddle_re * im[match];
        re[match] = re[pair] - product_re;
        im[match] = im[pair] - product_im;
        re[pair] += product_re;
        im[pair] += product_im;
    }
}
static inline void __iterate_groups(float *re, float *im, const unsigned int step, const unsigned int N)
{
    const float pi = -3.14159265358979323846;
    float twiddle_re = 1.0;
    float twiddle_im = 0.0;
    for (unsigned int group = 0; group < step; group++)
    {
        __iterate_pairs(re, im, group, step, N, twiddle_re, twiddle_im);
        if (group + 1 == step)
        {
            continue;
        }

        float angle = pi * ((float)group + 1) / (float)step;
        twiddle_re = cos(angle);
        twiddle_im = sin(angle);
    }
}

static void __compute(float *re, float *im, const unsigned int N)
{

    for (unsigned int step = 1; step < N; step <<= 1)
    {
        __iterate_groups(re, im, step, N);
    }
}
void fft(float *re, float *im, const unsigned int N)
{
    __rearrange(re, im, N);
    __compute(re, im, N);
}