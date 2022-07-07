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

#define IMG_HEIGHT 28
#define IMG_WIDTH 28
#define IMG_SIZE IMG_HEIGHT * IMG_WIDTH

/** @brief MNIST dataset images.*/
typedef Data Image;

/** @brief Contains all the necessary data to parse the MNIST CSV.*/
typedef struct ImageSetMetadata {
    char fileName[128];
    int noOfImages;
} ImageSetMetadata;

/** @brief The dataset type to be parsed. */
typedef enum DatasetType { TRAINING, TESTING } DatasetType;

/** @brief Read Image Dataset.
 * 
 *  @param dest The destination array where all the images
 *  are to be stored.
 *  @param size The size of the destination array.
 *  @param meta The metadata for the Mnist CSV to be used.
 *  @return Void.
 */
void readImageSet(Image dest[], int size, ImageSetMetadata meta); 
/** @brief Gets the metadata of the dataset type to be parsed
 *  from the MNIST image dataset.
 * 
 *  @param type The type of dataset to be parsed.
 *  @return The metadata for the CSV of that dataset.
 */
ImageSetMetadata getMetadata(DatasetType type);
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