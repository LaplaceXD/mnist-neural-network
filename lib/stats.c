/** @file stats.c
 *  @brief A utility functions library which contains
 *  different stats functions.
 *
 *  This library contains functions various statistical 
 *  operations on arrays, such as min, max, standard deviation,
 *  averaging, and data transformation.
 *
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No know bugs.
 */
#include <stdio.h>
#include <math.h>
#include "headers/stats.h"

#define throwInvalidArgs(arg, msg) { fprintf(stderr, "Invalid %s Argument. %s", arg, msg); exit(1); }
#define SHOULD_BE_POSITIVE "It should be a positive integer."

int isDoubleEq(double x, double y)
{
    return fabs(x - y) <= __DBL_EPSILON__;
}

double min(double arr[], int size)
{
    if(size <= 0) throwInvalidArgs("size", SHOULD_BE_POSITIVE);
    
    int idx;
    double minimum;

    minimum = arr[0];
    for(idx = 1; idx < size; idx++) {
        if(!isDoubleEq(arr[idx], minimum) && arr[idx] < minimum) {
            minimum = arr[idx];
        }
    }

    return minimum;
}

double max(double arr[], int size)
{
    if(size <= 0) throwInvalidArgs("size", SHOULD_BE_POSITIVE);
    
    int idx;
    double maximum;

    maximum = arr[0];
    for(idx = 1; idx < size; idx++) {
        if(!isDoubleEq(arr[idx], maximum) && arr[idx] > maximum) {
            maximum = arr[idx];
        }
    }

    return maximum;
}

double average(double arr[], int size)
{
    if(size <= 0) throwInvalidArgs("size", SHOULD_BE_POSITIVE);
    
    int idx;
    double sum;

    sum = 0;
    for(idx = 0; idx < size; idx++) {
        sum += arr[idx];
    }

    return sum / size;
}

double stddev(double arr[], int size)
{
    if(size <= 0) throwInvalidArgs("size", SHOULD_BE_POSITIVE);
    
    int idx;
    double sumOfSquares, mean, diff;

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

void normalize(double arr[], int size)
{
    if(size <= 0) throwInvalidArgs("size", SHOULD_BE_POSITIVE);
    
    int idx; 
    double minimum, maximum, range;

    minimum = min(arr, size);
    maximum = max(arr, size);
    range = maximum - minimum;
    
    if(!isDoubleEq(range, 0)) {
        for(idx = 0; idx < size; idx++) {
            arr[idx] = (arr[idx] - minimum) / range;
        }
    }
}

void standardize(double arr[], int size)
{
    if(size <= 0) throwInvalidArgs("size", SHOULD_BE_POSITIVE);
    
    int idx;
    double mean, sdev;
    
    mean = average(arr, size);
    sdev = stddev(arr, size);
    
    if(!isDoubleEq(sdev, 0)) {
        for(idx = 0; idx < size; idx++) {
            arr[idx] = (arr[idx] - mean) / sdev;
        }
    }
}
