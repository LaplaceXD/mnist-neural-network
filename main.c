#include <stdio.h>
#include <math.h>
#include <time.h>
#include "lib/headers/stats.h"
#include "lib/headers/image_set.h"
#include "lib/headers/neural_net.h"
#include "lib/headers/ml.h"

int main(int argc, char **argv)
{
    srand((unsigned int) time(NULL)); // initialize randomizer

    int layerSizes[] = { IMG_SIZE, 16, 16, 10 };
    
    NeuralNetOpt opt = getDefaultOptions();
    opt.layerSizes = layerSizes;
    opt.neuralNetSize = sizeof(layerSizes) / sizeof(int);
    
    NeuralNetwork nn = createNeuralNet(opt);

    /* =============== TRAINING ================== */
    ImageSetMetadata metadata = getMetadata(TRAINING);
    int imagesetSize = metadata.noOfImages;

    Image trainImgs[imagesetSize];
    readImageSet(trainImgs, imagesetSize, metadata);
    prepDataset(trainImgs, imagesetSize, nn.options.nodeOrient, normalize);

    int epoch;
    for(epoch = 1; epoch <= 20; epoch++) {
        printf("EPOCH: %d\n", epoch);
        networkTrain(nn, reLU, 20, trainImgs, imagesetSize);
    }

    freeImageSet(trainImgs, imagesetSize);
    /* =========== END OF TRAINING ============== */

    /* =============== TESTING ================== */
    metadata = getMetadata(TESTING);
    imagesetSize = metadata.noOfImages;
    
    Image testImgs[imagesetSize];
    readImageSet(testImgs, imagesetSize, metadata);
    prepDataset(testImgs, imagesetSize, nn.options.nodeOrient, normalize);

    double acc = networkTest(nn, reLU, testImgs, imagesetSize);
    printf("\nAccuracy: %.2lf percent.", acc * 100);

    freeImageSet(testImgs, imagesetSize);
    /* =========== END OF TESTING ============== */

    freeNeuralNet(&nn);

    return 0;
}
