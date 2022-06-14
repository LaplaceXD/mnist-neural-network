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

void normalizeImage(Image *img)
{
    int row, size = img->pixels.row * img->pixels.col;
    double pixelBuffer[size], *bufferPos;

    for(row = 0; row < img->pixels.row; row++) {
        bufferPos = pixelBuffer + row * img->pixels.col;
        memcpy(bufferPos, img->pixels.entries[row], sizeof(double) * img->pixels.col);
    }

    normalizeData(pixelBuffer, size);

    for(row = 0; row < img->pixels.row; row++) {
        bufferPos = pixelBuffer + row * img->pixels.col;
        memcpy(img->pixels.entries[row], bufferPos, sizeof(double) * img->pixels.col);
    }
}

void batchNormalizeImages(Image *imgs, int size)
{
    int idx;
    for(idx = 0; idx < size; idx++) {
        normalizeImage(imgs+idx);
    }
}