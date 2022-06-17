/** @file util.h
 *  @brief Function prototypes for the util library.
 *
 *  This contains the prototypes, type definitions,
 *  constants, and globals for the util library.
 * 
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No known bugs.
 */
#pragma once

#include <stdio.h>
#include <stdlib.h>

#define InitReadCSVFunc(DATA_TYPE, FOR) \
/** @brief A function that reads data from a csv.
 * 
 *  Each row in the csv is held inside a buffer,
 *  thus the bufferSize must conform to how long
 *  the longest row in the CSV is. Each of these buffer
 *  is then passed to a callback function, where the user
 *  can retrieve the data from each row.
 * 
 *  @note You must first define the DATA_TYPE to the structure
 *  of your dataset before using this function.
 * 
 *  @param dest The destination array, where all of the data
 *  returned from the callback are stored.
 *  @param fileName The name of the csv to be read.
 *  @param rows The number of row to be read from the csv.
 *  @param rowSize The size of each rows in the csv including
 *  the delimiters.
 *  @param cb The callback function where the user can manipulate
 *  the buffer returned by the function, and then return the
 *  appropriate data that is to be stored in dest.
 *  @return Void.
 */ \
void read##FOR##CSV(DATA_TYPE *dest, char *fileName, int rows, int rowSize, DATA_TYPE (*cb)(char *buffer)) \
{ \
    if(rows <= 0 || rowSize <= 0) { \
        fprintf(stderr, "CSV Reading Failed. Rows and their sizes should be a positive integer."); \
        exit(1); \
    } \
    if(cb == NULL) { \
        fprintf(stderr, "CSV Reading Failed. Callback can't be NULL."); \
        exit(1); \
    } \
     \
    int idx; \
    char rowBuffer[rowSize]; \
    FILE* csv = fopen(strcat(fileName, ".csv"), "r"); \
    if(csv == NULL) { \
        fprintf(stderr, "CSV Reading Failed. Unable to open file."); \
        exit(1); \
    } \
     \
    for(idx = 0; idx < rows && fgets(rowBuffer, rowSize, csv); idx++) { \
        dest[idx] = cb(rowBuffer); \
    } \
     \
    fclose(csv); \
}

/** @brief Type definition for Data Transforming functions. */
typedef void (*TransformCallback)(double *data, int size);

/** @brief Returns the minimum value in an array.
 * 
 * @param data An array of values.
 * @param size The size of the array.
 * @return The minimum value of an array.
 */
double min(double * data, int size);
/** @brief Returns the maximum value in an array.
 * 
 * @param data An array of values.
 * @param size The size of the array.
 * @return The maximum value of an array.
 */
double max(double * data, int size);
/** @brief Calculates the average value of an array.
 * 
 * @param data An array of values.
 * @param size The size of the array.
 * @return The average value of an array.
 */
double average(double * data, int size);
/** @brief Calculates the standard deviation of
 * the values in an array.
 * 
 * @param data An array of values.
 * @param size The size of the array.
 * @return The standard deviation of an array.
 */
double stddev(double * data, int size);
/** @brief Returns a random number within the range [min, max].
 * 
 * @param min The minimum possible random number.
 * @param max The maximum possible random number.
 * @return A random number between min and max.
 */
double randn(double min, double max);
/** @brief Normalizes the values in an array.
 * 
 * This is calculated by scaling subtracting
 * each value by the minimum and dividing them
 * by the range of the dataset.
 * 
 * @param data An array containing all the values to normalize.
 * @param size The size of the array.
 * @return Void.
 */
void normalize(double * data, int size);
/** @brief Standardizes the values in an array.
 * 
 * This is calculated by subtracting the mean
 * of the dataset to each data in the set, and 
 * then dividing them with the standard deviation
 * of the set.
 * 
 * @param data An array containing all the values to standardize.
 * @param size The size of the array.
 * @return Void.
 */
void standardize(double * data, int size);