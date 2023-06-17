#ifndef LIBSIGGEN_H
#define LIBSIGGEN_H
#include <complex.h>

void generate_saw(float complex *buffer, const unsigned int N);
void generate_square(float complex *buffer, const unsigned int N);
void generate_triangle(float complex *buffer, const unsigned int N);
void generate_sin(float complex *buffer, const unsigned int N);

#endif