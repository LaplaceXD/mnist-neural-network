/** @file mnist_img.c
 *  @brief A library made for working with mnist
 *  digit dataset.
 *
 *  This library contains the constants for the data
 *  to be used in training and testing the neural network.
 *  It also has functions for reading image to buffer, 
 *  reading the MNIST CSV and transforming images pixel
 *  values to normalized or standardized forms.
 *
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No know bugs.
 */

#include <string.h>
#include <stdlib.h>
#include "headers/data.h"
#include "headers/mnist_img.h"

ReadCSVDataType(Image);

const MnistMetadata TRAIN_DATA = {
    "dataset/mnist_train",
    60000,
    BUFFER_SIZE
};

const MnistMetadata TEST_DATA = {
    "dataset/mnist_test",
    10000,
    BUFFER_SIZE
};

void readMnistCSV(Image *dest, MnistMetadata meta)
{
    readCSVData(dest, meta.fileName, meta.imgCount, meta.imgBufferSize, bufferToImage);
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
    int row, size = img->pixels.row * img->pixels.col;
    double pixelBuffer[size], *bufferPos;

    for(row = 0; row < img->pixels.row; row++) {
        bufferPos = pixelBuffer + row * img->pixels.col;
        memcpy(bufferPos, img->pixels.entries[row], sizeof(double) * img->pixels.col);
    }

    transform(pixelBuffer, size);

    for(row = 0; row < img->pixels.row; row++) {
        bufferPos = pixelBuffer + row * img->pixels.col;
        memcpy(img->pixels.entries[row], bufferPos, sizeof(double) * img->pixels.col);
    }
}

void batchTransformImages(Image *imgs, int size, TransformFunc transform)
{
    if(size <= 0) {
        fprintf(stderr, "Standardization Failed. Size should be a positive integer.");
        exit(1);
    }
    
    int idx;
    for(idx = 0; idx < size; idx++) {
        transformImage(imgs+idx, transform);
    }
}

void freeImages(Image *imgs, int size)
{
    int idx;
    for(idx = 0; idx < size; idx++) {
        imgs[idx].value = 0;
        freeMatrix(&imgs[idx].pixels);
    }
}