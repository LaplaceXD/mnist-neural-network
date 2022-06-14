#include <stdio.h>
#include "lib/headers/mnist_img.h"
#include "lib/headers/data.h"
#include "lib/headers/matrix.h"

int main(int argc, char **argv)
{
    const MnistMetadata trainData = TRAIN_DATA;
    
    int idx;

    Image imgs[trainData.imgCount];
    readMnistCSV(imgs, trainData);
    
    printf("=================%d : %d ================\n", 1, imgs[0].value);
    printMatrix(imgs[0].pixels);
    printf("\n");

    batchTransformImages(imgs, trainData.imgCount, standardizeValues);
    
    printf("=================%d : %d ================\n", 1, imgs[0].value);
    printMatrix(imgs[0].pixels);
    printf("\n");

    for(idx = 0; idx < trainData.imgCount; idx++) {
        freeMatrix(&imgs[idx].pixels);
    }

    return 0;
}