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

#define BUFFER_SIZE 2048

void readImageSet(Image dest[], int size, ImageSetMetadata meta)
{
    if(size <= 0) throwInvalidArgs("size", SHOULD_BE_POSITIVE);
    if(!isValidMetadata(meta)) throwInvalidArgs("meta", NOT_VALID_METADATA);

    int idx;
    char buffer[BUFFER_SIZE];
    FILE *fp = fopen(meta.fileName, "r");
    if(fp == NULL) throwInvalidArgs("meta file name", "Unable to open file.");

    for(idx = 0; idx < size && fgets(buffer, BUFFER_SIZE, fp); idx++) {
        dest[idx] = bufferToImage(buffer);
    } 

    fclose(fp);
}

ImageSetMetadata getMetadata(DatasetType type)
{
    ImageSetMetadata meta;

    switch(type) {
        case TRAINING:
            strcpy(meta.fileName, "dataset/mnist_train.csv");
            meta.noOfImages = 60000;
            break;
        case TESTING:
            strcpy(meta.fileName, "dataset/mnist_test.csv");
            meta.noOfImages = 10000;
            break;
        default:
            throwInvalidArgs("type", "");
    }

    return meta;
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
    int hasValidNoOfImages = metadata.noOfImages > 0;

    return hasValidNoOfImages ? 1 : 0;
}