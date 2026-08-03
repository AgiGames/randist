#ifndef RANDIST_H
#define RANDIST_H

#include <pcg_variants.h>

#include <stdlib.h>

void randist(double* array, size_t size, 
        pcg32_random_t* rng, 
        double x_low, double x_high, 
        double (*probdist)(double));

void randist_uniform(double* array, size_t size, pcg32_random_t* rng, double low, double high);

#endif
