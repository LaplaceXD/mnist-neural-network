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
#include "headers/stats.h"
#include "headers/matrix.h"
#include "headers/image_set.h"

#define throwInvalidArgs(arg, msg) { fprintf(stderr, "Invalid %s Argument. %s", arg, msg); exit(1); }
#define SHOULD_BE_POSITIVE "It should be a positive integer."
#define SHOULD_NOT_BE_NULL "Argument should not be null."
#define NOT_VALID_METADATA "Metadata contains invalid values."

const ImageSetMetadata TRAIN_DATA = {
    "dataset/mnist_train.csv",
    60000,
    BUFFER_SIZE_DEFAULT
};

const ImageSetMetadata TEST_DATA = {
    "dataset/mnist_test.csv",
    10000,
    BUFFER_SIZE_DEFAULT
};

void readImageSet(Image dest[], int size, ImageSetMetadata meta)
{
    if(size <= 0) throwInvalidArgs("size", SHOULD_BE_POSITIVE);
    if(!isValidMetadata(meta)) throwInvalidArgs("meta", NOT_VALID_METADATA);

    int idx;
    char buffer[meta.BUFFER_SIZE];
    FILE *fp = fopen(meta.FILE_NAME, "r");
    if(fp == NULL) throwInvalidArgs("meta", "Unable to open file.");

    for(idx = 0; idx < size && fgets(buffer, meta.BUFFER_SIZE, fp); idx++) {
        dest[idx] = bufferToImage(buffer);
    } 

    fclose(fp);
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

void transformImage(Image *img, TransformFunc transform)
{
    if(transform == NULL) throwInvalidArgs("transform", SHOULD_NOT_BE_NULL);
    
    int row, size = img->pixels.row * img->pixels.col;
    double pixelBuffer[size], *bufferPos;

    copyMatrixToArr(img->pixels, pixelBuffer, size);
    transform(pixelBuffer, size);
    copyArrToMatrix(pixelBuffer, size, img->pixels);
}

void transformImageSet(Image imgs[], int size, TransformFunc transform)
{
    if(size <= 0) throwInvalidArgs("size", SHOULD_BE_POSITIVE);
    if(transform == NULL) throwInvalidArgs("transform", SHOULD_NOT_BE_NULL);

    int idx;
    for(idx = 0; idx < size; idx++) {
        transformImage(imgs+idx, transform);
    }
}

void freeImageSet(Image imgs[], int size)
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