#include <pcg_variants.h>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/randist.h"

double rand_uniform(pcg32_random_t* rng, double low, double high) {
    return (high - low) * ldexp((double)pcg32_random_r(rng), -32) + low;
}

double rand_uniform_discrete(pcg32_random_t* rng, double low, double high, double step) {
    int temp = (high - low) * ldexp((double)pcg32_random_r(rng), -32) / step;
    return (double)temp * step + low;
}

void randist_uniform(double* array, size_t size, pcg32_random_t* rng, double low, double high) {
    for (size_t i = 0; i < size; ++i) {
        array[i] = (high - low) * ldexp((double)pcg32_random_r(rng), -32) + low;
    }
}

void randist_uniform_discrete(double* array, size_t size, pcg32_random_t* rng, double low, double high, double step) {
    for (size_t i = 0; i < size; ++i) {
        int temp = (high - low) * ldexp((double)pcg32_random_r(rng), -32) / step;
        array[i] = (double)temp * step + low;
    }
}

double find_derivative(double (*f)(double), double x) {
    double eps = 1e-6;
    return (f(x + eps) - f(x - eps)) / 2 * eps;
}

double find_maxima(double x_low, double x_high, double (*probdist)(double)) {
    const double eps = 1e-6;

    while (x_high - x_low > eps) {
        double mid = x_low + ((x_high - x_low) / 2);
        double slope = find_derivative(probdist, mid);
        if (slope > 0.0) {
            x_low = mid;    
        }
        else {
            x_high = mid;
        }
    }

    return probdist(x_low + ((x_high - x_low) / 2));
}

void randist(double* array, size_t size, 
        pcg32_random_t* rng, 
        double x_low, double x_high, 
        double (*probdist)(double)) {

    if (probdist == NULL) {
        randist_uniform(array, size, rng, x_low, x_high);
        return;
    }

    double y_max = find_maxima(x_low, x_high, probdist);
    size_t i = 0;
    while (i < size) {
        double xi = rand_uniform(rng, x_low, x_high);
        double yi = rand_uniform(rng, 0, y_max);

        double yi_cap = probdist(xi);
        if (yi > yi_cap) continue;

        array[i] = xi;
        ++i;
    }
}

void randist_discrete(double* array, size_t size, 
        pcg32_random_t* rng, 
        double x_low, double x_high, 
        double (*probdist)(double),
        double x_step, double y_step) {

    if (probdist == NULL) {
        randist_uniform_discrete(array, size, rng, x_low, x_high, x_step);
    }

    double y_max = find_maxima(x_low, x_high, probdist);
    size_t i = 0;
    while (i < size) {
        double xi = rand_uniform_discrete(rng, x_low, x_high, x_step);
        double yi = rand_uniform_discrete(rng, 0, y_max, y_step);

        double yi_cap = probdist(xi);
        if (yi > yi_cap) continue;

        array[i] = xi;
        ++i;
    }
}
