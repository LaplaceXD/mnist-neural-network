/** @file mnist_img.c
 *  @brief A library made for working with mnist
 *  digit image set.
 *
 *  This library contains the constants for the data
 *  to be used in training and testing the neural network.
 *  It also has functions for reading image to buffer, and
 *  reading the MNIST CSV.
 *
 *  DEPENDENCIES: matrix, ml
 * 
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No know bugs.
 */

#include <string.h>
#include <stdlib.h>
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
        .expVal = atoi(strtok(buffer, ",")),
        .inputValues = createMatrix(IMG_HEIGHT, IMG_WIDTH)
    };

    for(row = 0; row < img.inputValues.row; row++) {
        for(col = 0; col < img.inputValues.col; col++) {
            img.inputValues.entries[row][col] = atoi(strtok(NULL, ","));
        }
    }

    return img;
}

void freeImageSet(Image imgs[], int size)
{
    int idx;
    for(idx = 0; idx < size; idx++) {
        imgs[idx].expVal = 0;
        freeMatrix(&imgs[idx].inputValues);
    }
}

int isValidMetadata(ImageSetMetadata metadata)
{
    int hasValidSize = metadata.SIZE > 0;
    int hasValidBufferSize = metadata.BUFFER_SIZE > 0;

    return hasValidSize && hasValidBufferSize ? 1 : 0;
}