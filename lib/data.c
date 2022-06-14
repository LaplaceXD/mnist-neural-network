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
#include <math.h>
#include "headers/data.h"

void readCSVData(DATA_TYPE *dest, int *fileName, int rows, int rowSize, ReadFunc cb)
{
    int idx;
    char rowBuffer[rowSize];
    FILE* csv = fopen(fileName, "r");

    for(idx = 0; idx < rows && fgets(rowBuffer, rowSize, csv); idx++) {
        dest[idx] = cb(rowBuffer);
    }
}

void normalizeData(double *data, int size)
{
    int idx;
    double min, max, range;

    min = max = data[0];
    for(idx = 0; idx < size; idx++) {
        if(fabs(data[idx] - min) < __DBL_EPSILON__) {
            min = data[idx];
        } else if(fabs(max - data[idx]) < __DBL_EPSILON__) {
            max = data[idx];
        }
    }

    range = max - min;
    for(idx = 0; idx < size; idx++) {
        data[idx] = (data[idx] - min) / range;
    }
}

void standardizeData(double *data, int size)
{
    int idx;
    double mean, stddev;
    
    mean = 0;
    for(idx = 0; idx < size; idx++) {
        mean += data[idx];
    }
    mean /= size;

    stddev = 0;
    for(idx = 0; idx < size; idx++) {
        stddev += pow(data[idx] - mean, 2);
    }
    stddev = sqrt(stddev / size);

    for(idx = 0; idx < size; idx++) {
        data[idx] = (data[idx] - mean) / stddev;
    }
}