/** @file util.c
 *  @brief A utility functions library which contains
 *  basic auxilliary function.
 *
 *  This library contains functions for CSV reading,
 *  extra math functions, and random number generators.
 *
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No know bugs.
 */

#include <stdio.h>
#include <math.h>
#include "headers/util.h"

int isDoubleEq(double x, double y)
{
    return fabs(x - y) <= __DBL_EPSILON__;
}

double min(double *arr, int size)
{
    int idx;
    double minimum;
    
    if(size <= 0) {
        fprintf(stderr, "Size should be a positive integer.");
        exit(1);
    }

    minimum = arr[0];
    for(idx = 1; idx < size; idx++) {
        if(!isDoubleEq(arr[idx], minimum) && arr[idx] < minimum) {
            minimum = arr[idx];
        }
    }

    return minimum;
}

double max(double *arr, int size)
{
    int idx;
    double maximum;
    
    if(size <= 0) {
        fprintf(stderr, "Size should be a positive integer.");
        exit(1);
    }

    maximum = arr[0];
    for(idx = 1; idx < size; idx++) {
        if(!isDoubleEq(arr[idx], maximum) && arr[idx] > maximum) {
            maximum = arr[idx];
        }
    }

    return maximum;
}

double average(double *arr, int size)
{
    int idx;
    double sum;
    
    if(size <= 0) {
        fprintf(stderr, "Size should be a positive integer.");
        exit(1);
    }

    sum = 0;
    for(idx = 0; idx < size; idx++) {
        sum += arr[idx];
    }

    return sum / size;
}

double stddev(double *arr, int size)
{
    int idx;
    double sumOfSquares, mean, diff;

    if(size <= 0) {
        fprintf(stderr, "Size should be a positive integer.");
        exit(1);
    }

    mean = average(arr, size);
    sumOfSquares = 0;
    for(idx = 0; idx < size; idx++) {
        diff = arr[idx] - mean;
        sumOfSquares += diff * diff; 
    }

    return sqrt(sumOfSquares / size);
}

double randn(double min, double max) 
{
    double range = max - min; 
    return min + ((double) rand() / RAND_MAX) * range;
}

void normalize(double *data, int size)
{
    int idx; 
    double minimum, maximum, range;

    if(size <= 0) {
        fprintf(stderr, "Normalization failed. Size should be a positive integer.");
        exit(1);
    }

    minimum = min(data, size);
    maximum = max(data, size);
    range = minimum - maximum;
    
    if(!isDoubleEq(range, 0)) {
        for(idx = 0; idx < size; idx++) {
            data[idx] = (data[idx] - minimum) / range;
        }
    }
}

void standardize(double *data, int size)
{
    int idx;
    double mean, sdev;
    
    if(size <= 0) {
        fprintf(stderr, "Standardization Failed. Size should be a positive integer.");
        exit(1);
    }
    
    mean = average(data, size);
    sdev = stddev(data, size);
    
    if(!isDoubleEq(sdev, 0)) {
        for(idx = 0; idx < size; idx++) {
            data[idx] = (data[idx] - mean) / sdev;
        }
    }
}
