#include <pcg_variants.h>

#include <math.h>
#include <stdio.h>

#include "../include/randist.h"

#define MAX_SIZE 1000

double normal_probdist(double x) {
    return (1 / sqrt(2 * M_PI)) * exp(-(x * x / 2));
}

double laplace_probdist(double x) {
    return 0.5 * exp(-fabs(x));
}

double exponential_probdist(double x) {
    return exp(-x);
}

double poisson_probdist(double x) {
    return pow(1.0, x) * exp(-1.0) / tgamma(x + 1);
}

int main() {
    double array[MAX_SIZE];
    
    pcg32_random_t rng;
    pcg32_srandom_r(&rng, 42u, 52u);
    
    randist(array, MAX_SIZE, &rng, -50, 50, normal_probdist);
    FILE *fp = fopen("samples.txt", "w");
    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    for (size_t i = 0; i < MAX_SIZE; ++i) {
        fprintf(fp, "%lf", array[i]);
        if (i != MAX_SIZE - 1) {
            fprintf(fp, ",");
        }
    }

    return 0;
}
