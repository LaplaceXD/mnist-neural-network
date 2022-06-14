/** @file mnist_img.h
 *  @brief Function prototypes for the mnist img library.
 *
 *  This contains the prototypes, type definitions,
 *  constants, and globals for the mnist img library.
 * 
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No known bugs.
 */

#ifndef _MNIST_IMG_H
#define _MNIST_IMG_H
#define DATA_TYPE Image

#include "headers/data.h"
#include "headers/matrix.h"

#define BUFFER_SIZE 2048
#define IMG_HEIGHT 28
#define IMG_WIDTH 28

/** @brief Stucture for MNIST dataset images.*/
typedef struct Image {
    int value;
    Matrix pixels; 
} Image;

/** @brief Contains all the necessary data to parse a CSV.*/
typedef struct CSVMetadata {
    char fileName[128];
    int imgCount;
    int imgBufferSize;
} MnistMetadata;

/** @brief Options for MNIST data training CSV.*/
const MnistMetadata TRAIN_DATA = {
    "dataset/mnist_train",
    60000,
    BUFFER_SIZE
};

/** @brief Options for MNIST data testing CSV.*/
const MnistMetadata TEST_DATA = {
    "dataset/mnist_test",
    10000,
    BUFFER_SIZE
};

/** @brief Read Mnist Dataset.
 * 
 *  @param dest The destination array where all the images
 *  are to be stored.
 *  @param meta The metadata for the Mnist CSV to be used.
 *  @return Void.
 */
void readMnistCSV(Image *dest, MnistMetadata meta); 
/** @brief Convert CSV rows into Image structs.
 * 
 *  @param buffer A string version of the rows of the CSV. 
 *  @return An Image struct containing the data parsed from
 *  the buffer.
 */
Image *bufferToImage(char *buffer);
/** @brief Normalizes image pixel values to ensure that the pixel values
 *  are withing the 0 to 1 range.
 * 
 *  @param img A pointer to an image, whose pixels are to be
 *  normalized. 
 *  @return Void.
 */
void normalizeImage(Image *img);
/** @brief Normalizes a batch of images in an array.
 * 
 *  @param imgs An array of images to be normalized. 
 *  @param size The size of the array. 
 *  @return Void.
 */
void batchNormalizeImages(Image *imgs, int size)

#endif