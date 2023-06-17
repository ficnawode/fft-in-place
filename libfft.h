#ifndef LIBFFT_H
#define LIBFFT_H
#include <complex.h>
#include <stdint.h>

void fft(float complex *data, const uint16_t N);

#endif