#include <stdio.h>
#include <math.h>
#include <time.h>
#include "lib/headers/mnist_img.h"
#include "lib/headers/neural_net.h"

int main(int argc, char **argv)
{
    srand((unsigned int) time(NULL)); // randomizer
    // Load Datasets
    printf("Loading Datasets...");
    Image trainingImgs[TRAIN_DATA.imgCount], testingImgs[TEST_DATA.imgCount];
    readMnistCSV(trainingImgs, TRAIN_DATA);
    readMnistCSV(testingImgs, TEST_DATA);
    printf(" DONE\n");

    // Normalize Datasets
    printf("Normalizing Datasets...");
    batchTransformImages(trainingImgs, TRAIN_DATA.imgCount, normalizeValues);
    batchTransformImages(testingImgs, TEST_DATA.imgCount, normalizeValues);
    printf(" DONE\n");

    // Create Neural Network
    printf("Creating Neural Network...");
    LayerDesign layers[] = {{IMG_SIZE, INPUT}, {16, HIDDEN}, {16, HIDDEN}, {10, OUTPUT}};
    NeuralNetOpt opt = createNeuralNetOpt(HE_XAVIER, 1, 1);
    NeuralNetwork nn = createNeuralNet(opt, layers, 4);
    printf(" DONE\n");

    // WIP

    // Cleanup
    printf("Cleaning up...");
    freeNeuralNet(&nn);
    freeImages(trainingImgs, TRAIN_DATA.imgCount);
    freeImages(testingImgs, TEST_DATA.imgCount);
    printf(" DONE\n");

    return 0;
}
