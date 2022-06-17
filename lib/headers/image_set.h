/** @file mnist_img.h
 *  @brief Function prototypes for the image set library.
 *
 *  This contains the prototypes, type definitions,
 *  constants, and globals for the image set library.
 * 
 *  DEPENDENCIES: util, matrix
 * 
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No known bugs.
 */
#pragma once

#include "matrix.h"
#include "util.h"

#define BUFFER_SIZE_DEFAULT 2048
#define IMG_HEIGHT 28
#define IMG_WIDTH 28
#define IMG_SIZE IMG_HEIGHT * IMG_WIDTH

/** @brief Stucture for MNIST dataset images.*/
typedef struct Image {
    int value;
    Matrix pixels; 
} Image;

/** @brief Contains all the necessary data to parse a CSV.*/
typedef struct CSVMetadata {
    char FILE_NAME[128];
    int SIZE;
    int BUFFER_SIZE;
} ImageSetMetaData;

/** @brief Options for MNIST data training CSV.*/
extern const ImageSetMetaData TRAIN_DATA;  

/** @brief Options for MNIST data testing CSV.*/
extern const ImageSetMetaData TEST_DATA;

/** @brief Read Image Dataset.
 * 
 *  @param dest The destination array where all the images
 *  are to be stored.
 *  @param meta The metadata for the Mnist CSV to be used.
 *  @return Void.
 */
void readImageSet(Image *dest, ImageSetMetaData meta); 
/** @brief Convert CSV rows into Image structs.
 * 
 *  @param buffer A string version of the rows of the CSV. 
 *  @return An Image struct containing the data parsed from
 *  the buffer.
 */
Image bufferToImage(char *buffer);
/** @brief Normalizes image pixel values to ensure that the pixel values
 *  are withing the 0 to 1 range.
 * 
 *  @param img A pointer to an image, whose pixels are to be
 *  normalized.
 *  @param transformCb A transform callback function that \
 *  is used to convert the image values. 
 *  @return Void.
 */
void transformImage(Image *img, TransformCallback transformCb);
/** @brief Normalizes a batch of images in an array.
 * 
 *  @param imgs An array of images to be normalized. 
 *  @param size The size of the dataset. 
 *  @param transformCb A transform callback function that \
 *  is used to convert the image values. 
 *  @return Void.
 */
void transformImageSet(Image *imgs, int size, TransformCallback transformCb);
/** @brief Frees up loaded images from memory.
 * 
 *  @param imgs An array of images to be freed. 
 *  @param size The size of the dataset. 
 *  @return Void.
 */
void freeImageSet(Image *imgs, int size);