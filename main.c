#include <stdio.h>
#include <math.h>
#include <time.h>
#include "lib/headers/util.h"
#include "lib/headers/image_set.h"
#include "lib/headers/neural_net.h"

int main(int argc, char **argv)
{
    srand((unsigned int) time(NULL)); // initialize randomizer
 
    LayerDesign layers[] = {{IMG_SIZE, INPUT}, {16, HIDDEN}, {16, HIDDEN}, {10, OUTPUT}};
    NeuralNetOpt opt = { .distStrat = HE_XAVIER, .distSize = 1, .initialBias = 1 };
    NeuralNetwork nn = createNeuralNet(opt, layers, 4);
    
    /* =============== TRAINING ================== */
    Image trainImgs[TRAIN_DATA.SIZE];
    readImageSet(trainImgs, TRAIN_DATA);
    transformImageSet(trainImgs, TRAIN_DATA.SIZE, normalize);

    // WIP

    freeImageSet(trainImgs, TRAIN_DATA.SIZE);
    /* =========== END OF TRAINING ============== */

    /* =============== TESTING ================== */
    Image testImgs[TEST_DATA.SIZE];
    readImageSet(testImgs, TEST_DATA);
    transformImageSet( testImgs, TEST_DATA.SIZE, normalize);

    // WIP

    freeImageSet(testImgs, TEST_DATA.SIZE);
    /* =========== END OF TESTING ============== */

    freeNeuralNet(&nn);

    return 0;
}
