/** @file data.h
 *  @brief Function prototypes for data library.
 *
 *  This contains the prototypes, type definitions,
 *  constants, and globals for the data library.
 * 
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No known bugs.
 */
#ifndef _DATA_H
#define _DATA_H

#include <stdio.h>

#define ReadCSVDataType(DATA_TYPE) \
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
 *  @return Void. \
 */ \
void readCSVData(DATA_TYPE *dest, char *fileName, int rows, int rowSize, DATA_TYPE (*cb)(char *buffer)) \
{ \
    if(rows <= 0 || rowSize <= 0) { \
        fprintf(stderr, "CSV Reading Failed. Rows and their sizes should be a positive integer."); \
        exit(1); \
    } \
     \
    int idx; \
    char rowBuffer[rowSize]; \
    FILE* csv = fopen(strcat(fileName, ".csv"), "r"); \
     \
    for(idx = 0; idx < rows && fgets(rowBuffer, rowSize, csv); idx++) { \
        dest[idx] = cb(rowBuffer); \
    } \
}

/** @brief Type definition for Data Transforming functions.
 */
typedef void (*TransformFunc)(double *data, int size);

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
void normalizeValues(double * data, int size);
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
void standardizeValues(double * data, int size);

#endif /* _DATA_H */