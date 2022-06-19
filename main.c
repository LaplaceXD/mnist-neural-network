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

    LayerDesign layers[] = {{10, INPUT}, {5, HIDDEN}, {4, HIDDEN}, {10, OUTPUT}};
    NeuralNetOpt opt = { .distSize = 1, .distStrat = HE, .initialBias = 0, .nodeOrient = ROW, .lr = 0.1 };
    NeuralNetwork nn = createNeuralNet(opt, layers, 4);

    /* =============== TRAINING ================== */
    Image trainImgs[TRAIN_DATA.SIZE];
    readImageSet(trainImgs, TRAIN_DATA.SIZE, TRAIN_DATA);
    
    // flatten to node orientation, normalzie values
    prepDataset(trainImgs, TRAIN_DATA.SIZE, nn.options.nodeOrient, normalize);

    // WIP

    freeImageSet(trainImgs, TRAIN_DATA.SIZE);
    /* =========== END OF TRAINING ============== */

    /* =============== TESTING ================== */
    Image testImgs[TEST_DATA.SIZE];
    readImageSet(testImgs, TRAIN_DATA.SIZE, TEST_DATA);

    // flatten to node orientation, normalize values
    prepDataset(testImgs, TEST_DATA.SIZE, nn.options.nodeOrient, normalize);

    // WIP

    freeImageSet(testImgs, TEST_DATA.SIZE);
    /* =========== END OF TESTING ============== */

    freeNeuralNet(&nn);

    return 0;
}
