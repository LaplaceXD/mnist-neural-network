/** @file stats.h
 *  @brief Function prototypes for the stats library.
 *
 *  This contains the prototypes, type definitions,
 *  constants, and globals for the stats library.
 * 
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No known bugs.
 */
#pragma once

#include <stdio.h>
#include <stdlib.h>

/** @brief Type definition for Array Transforming functions. */
typedef void (*TransformFunc)(double arr[], int size);

/** @brief Checks if two doubles are equal.
 * 
 *  @param x A double.
 *  @param y A double.
 *  @return 1 - If the two doubles are equal. 
 *  0 - If it is not.
 */
int isDoubleEq(double x, double y);
/** @brief Returns the minimum value in an array.
 * 
 * @param arr An array of values.
 * @param size The size of the array.
 * @return The minimum value of an array.
 */
double min(double arr[], int size);
/** @brief Returns the maximum value in an array.
 * 
 * @param arr An array of values.
 * @param size The size of the array.
 * @return The maximum value of an array.
 */
double max(double arr[], int size);
/** @brief Calculates the average value of an array.
 * 
 * @param arr An array of values.
 * @param size The size of the array.
 * @return The average value of an array.
 */
double average(double arr[], int size);
/** @brief Calculates the standard deviation of
 * the values in an array.
 * 
 * @param arr An array of values.
 * @param size The size of the array.
 * @return The standard deviation of an array.
 */
double stddev(double arr[], int size);
/** @brief Returns a random number within the range [min, max].
 * 
 * @param min The minimum possible random number.
 * @param max The maximum possible random number.
 * @return A random number between min and max.
 */
double randn(double min, double max);
/** @brief Normalizes the values in an array.
 * 
 * This is calculated by subtracting
 * each value in the array by the minimum and then dividing 
 * it by the range of the values in the array.
 * 
 * @param arr An array containing all the values to normalize.
 * @param size The size of the array.
 * @return Void.
 */
void normalize(double arr[], int size);
/** @brief Standardizes the values in an array.
 * 
 * This is calculated by subtracting the mean
 * of the array to each value, and then dividing
 * it with the standard deviation of the values 
 * int the array.
 * 
 * @param arr An array containing all the values to standardize.
 * @param size The size of the array.
 * @return Void.
 */
void standardize(double arr[], int size);