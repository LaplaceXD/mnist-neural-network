/** @file mnist_img.h
 *  @brief Function prototypes for the image set library.
 *
 *  This contains the prototypes, type definitions,
 *  constants, and globals for the image set library.
 * 
 *  DEPENDENCIES: matrix, ml
 * 
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No known bugs.
 */
#pragma once

#include "ml.h"

#define BUFFER_SIZE_DEFAULT 2048
#define IMG_HEIGHT 28
#define IMG_WIDTH 28
#define IMG_SIZE IMG_HEIGHT * IMG_WIDTH

/** @brief MNIST dataset images.*/
typedef Data Image;

/** @brief Contains all the necessary data to parse a CSV.*/
typedef struct CSVMetadata {
    char FILE_NAME[128];
    int SIZE;
    int BUFFER_SIZE;
} ImageSetMetadata;

/** @brief Options for MNIST data training CSV.*/
extern const ImageSetMetadata TRAIN_DATA;  

/** @brief Options for MNIST data testing CSV.*/
extern const ImageSetMetadata TEST_DATA;

/** @brief Read Image Dataset.
 * 
 *  @param dest The destination array where all the images
 *  are to be stored.
 *  @param size The size of the destination array.
 *  @param meta The metadata for the Mnist CSV to be used.
 *  @return Void.
 */
void readImageSet(Image dest[], int size, ImageSetMetadata meta); 
/** @brief Convert CSV rows into Image structs.
 * 
 *  @param buffer A string version of the rows of the CSV. 
 *  @return An Image struct containing the data parsed from
 *  the buffer.
 */
Image bufferToImage(char *buffer);
/** @brief Frees up loaded images from memory.
 * 
 *  @param imgs An array of images to be freed. 
 *  @param size The size of the dataset. 
 *  @return Void.
 */
void freeImageSet(Image imgs[], int size);
/** @brief Checks if the metadata has valid
 *  values.
 * 
 *  @param metadata The metadata to be checked.
 *  @return 1 - If the metadata is valid. 0 - If
 *  it is not.
 */
int isValidMetadata(ImageSetMetadata metadata);