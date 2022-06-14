/** @file data.c
 *  @brief A library made for working with data.
 *
 *  This library contains functions for normalization,
 *  standardization, and reading of data from a CSV.
 *
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No know bugs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "headers/data.h"

int isDoubleEq(double x, double y)
{
    return fabs(x - y) <= __DBL_EPSILON__;
}

void normalizeValues(double *data, int size)
{
    int idx, row, col; 
    double min, max, range;

    if(size <= 0) {
        fprintf(stderr, "Normalization failed. Size should be a positive integer.");
        exit(1);
    }

    min = max = data[0];
    for(idx = 1; idx < size; idx++) {
        if(!isDoubleEq(data[idx], min) && data[idx] < min) {
            min = data[idx];
        } else if (!isDoubleEq(data[idx], max) && data[idx] > max) {
            max = data[idx];
        }
    }

    range = max - min;
    if(!isDoubleEq(range, 0)) {
        for(idx = 0; idx < size; idx++) {
            data[idx] = (data[idx] - min) / range;
        }
    }
}

void standardizeValues(double *data, int size)
{
    int idx;
    double mean, stddev, diff;
    
    if(size <= 0) {
        fprintf(stderr, "Standardization Failed. Size should be a positive integer.");
        exit(1);
    }
    
    mean = 0;
    for(idx = 0; idx < size; idx++) {
        mean += data[idx];
    }
    mean /= size;

    stddev = 0;
    for(idx = 0; idx < size; idx++) {
        diff = data[idx] - mean;
        stddev += diff * diff;
    }
    stddev = sqrt(stddev / size);
    
    if(!isDoubleEq(stddev, 0)) {
        for(idx = 0; idx < size; idx++) {
            data[idx] = (data[idx] - mean) / stddev;
        }
    }
}