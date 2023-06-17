#ifndef LIBSIGGEN_H
#define LIBSIGGEN_H

void generate_saw(float *re, float *im, const unsigned int N);
void generate_square(float *re, float *im, const unsigned int N);
void generate_triangle(float *re, float *im, const unsigned int N);
void generate_sin(float *re, float *im, const unsigned int N);

#endif