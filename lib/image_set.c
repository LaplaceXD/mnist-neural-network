/** @file mnist_img.c
 *  @brief A library made for working with mnist
 *  digit image set.
 *
 *  This library contains the constants for the data
 *  to be used in training and testing the neural network.
 *  It also has functions for reading image to buffer, 
 *  reading the MNIST CSV and transforming images pixel
 *  values.
 *
 *  DEPENDENCIES: util, matrix
 * 
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No know bugs.
 */

#include <string.h>
#include <stdlib.h>
#include "headers/util.h"
#include "headers/matrix.h"
#include "headers/image_set.h"

#define throwInvalidArgs(arg, msg) { fprintf(stderr, "Invalid %s Argument. %s", arg, msg); exit(1); }
#define SHOULD_BE_POSITIVE "It should be a positive integer."
#define SHOULD_NOT_BE_NULL "Argument should not be null."
#define NOT_VALID_METADATA "Metadata contains invalid values."

InitReadCSVFunc(Image, Mnist);

const ImageSetMetadata TRAIN_DATA = {
    "dataset/mnist_train",
    60000,
    BUFFER_SIZE_DEFAULT
};

const ImageSetMetadata TEST_DATA = {
    "dataset/mnist_test",
    10000,
    BUFFER_SIZE_DEFAULT
};

void readImageSet(Image *dest, ImageSetMetadata meta)
{
    if(!isValidMetadata(meta)) throwInvalidArgs("meta", NOT_VALID_METADATA);
    readMnistCSV(dest, meta.FILE_NAME, meta.SIZE, meta.BUFFER_SIZE, bufferToImage);
}

Image bufferToImage(char *buffer)
{
    int row, col;
    Image img = {
        .value = atoi(strtok(buffer, ",")),
        .pixels = createMatrix(IMG_HEIGHT, IMG_WIDTH)
    };

    for(row = 0; row < img.pixels.row; row++) {
        for(col = 0; col < img.pixels.col; col++) {
            img.pixels.entries[row][col] = atoi(strtok(NULL, ","));
        }
    }

    return img;
}

void transformImage(Image *img, TransformCallback transformCb)
{
    if(transformCb == NULL) throwInvalidArgs("transformCb", SHOULD_NOT_BE_NULL);
    
    int row, size = img->pixels.row * img->pixels.col;
    double pixelBuffer[size], *bufferPos;

    for(row = 0; row < img->pixels.row; row++) {
        bufferPos = pixelBuffer + row * img->pixels.col;
        memcpy(bufferPos, img->pixels.entries[row], sizeof(double) * img->pixels.col);
    }

    transformCb(pixelBuffer, size);

    for(row = 0; row < img->pixels.row; row++) {
        bufferPos = pixelBuffer + row * img->pixels.col;
        memcpy(img->pixels.entries[row], bufferPos, sizeof(double) * img->pixels.col);
    }
}

void transformImageSet(Image *imgs, int size, TransformCallback transformCb)
{
    if(size <= 0) throwInvalidArgs("size", SHOULD_BE_POSITIVE);
    if(transformCb == NULL) throwInvalidArgs("transformCb", SHOULD_NOT_BE_NULL);

    int idx;
    for(idx = 0; idx < size; idx++) {
        transformImage(imgs+idx, transformCb);
    }
}

void freeImageSet(Image *imgs, int size)
{
    int idx;
    for(idx = 0; idx < size; idx++) {
        imgs[idx].value = 0;
        freeMatrix(&imgs[idx].pixels);
    }
}

int isValidMetadata(ImageSetMetadata metadata)
{
    int hasValidSize = metadata.SIZE > 0;
    int hasValidBufferSize = metadata.BUFFER_SIZE > 0;

    return hasValidSize && hasValidBufferSize ? 1 : 0;
}