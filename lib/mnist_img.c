#include <string.h>
#include "headers/data.h"
#include "headers/mnist_img.h"

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