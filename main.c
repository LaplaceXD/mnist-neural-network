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

    LayerDesign layers[] = {{IMG_SIZE, INPUT}, {16, HIDDEN}, {16, HIDDEN}, {10, OUTPUT}};
    NeuralNetOpt opt = { .distSize = 1, .distStrat = RANDOM, .initialBias = 0, .nodeOrient = ROW, .lr = 0.1 };
    NeuralNetwork nn = createNeuralNet(opt, layers, sizeof(layers) / sizeof(LayerDesign));

    /* =============== TRAINING ================== */
    Image trainImgs[TRAIN_DATA.SIZE];
    readImageSet(trainImgs, TRAIN_DATA.SIZE, TRAIN_DATA);
    prepDataset(trainImgs, TRAIN_DATA.SIZE, nn.options.nodeOrient, normalize);

    int epoch;
    for(epoch = 1; epoch < 20; epoch++) {
        printf("EPOCH: %d\n", epoch);
        networkTrain(nn, sigmoid, 100, trainImgs, TRAIN_DATA.SIZE);
    }

    freeImageSet(trainImgs, TRAIN_DATA.SIZE);
    /* =========== END OF TRAINING ============== */

    /* =============== TESTING ================== */
    Image testImgs[TEST_DATA.SIZE];
    readImageSet(testImgs, TEST_DATA.SIZE, TEST_DATA);
    prepDataset(testImgs, TEST_DATA.SIZE, nn.options.nodeOrient, normalize);

    double acc = networkTest(nn, sigmoid, testImgs, TEST_DATA.SIZE);
    printf("\nAccuracy: %.2lf percent.", acc * 100);

    freeImageSet(testImgs, TEST_DATA.SIZE);
    /* =========== END OF TESTING ============== */

    freeNeuralNet(&nn);

    return 0;
}
