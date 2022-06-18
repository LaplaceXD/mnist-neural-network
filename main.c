#include <stdio.h>
#include <math.h>
#include <time.h>
#include "lib/headers/util.h"
#include "lib/headers/matrix.h"
#include "lib/headers/doubly_ll.h"
#include "lib/headers/image_set.h"
#include "lib/headers/neural_net.h"

// void printLayer(Layer l)
// {
//     char *type = l.type == INPUT ? "INPUT" : l.type == HIDDEN ? "HIDDEN" : "OUTPUT";

//     printf("Nodes: %d\n", l.nodes);
//     printf("Type: %s\n", type);
//     printf("====================WEIGHTS====================\n");
//     printMatrix(l.weights);
//     printf("=====================BIASES====================\n");
//     printMatrix(l.bias);
// }

int main(int argc, char **argv)
{
    Matrix m = createMatrix(2, 3);
    int num = 1, size = 10;
    for(int row = 0; row < m.row; row++) {
        for(int col = 0; col < m.col; col++) {
            m.entries[row][col] = num++;
        }
    }

    printMatrix(m);
    
    double arr[size];

    copyMatrixToArr(m, arr, size);
    for(num = 0; num < size; num++) printf("%.2lf ", arr[num]);
    
    // srand((unsigned int) time(NULL)); // initialize randomizer

    // LayerDesign layers[] = {{10, INPUT}, {5, HIDDEN}, {4, HIDDEN}, {10, OUTPUT}};
    // NeuralNetOpt opt = { .distStrat = HE_XAVIER, .distSize = 1, .initialBias = 0 };
    // NeuralNetwork nn = createNeuralNet(opt, layers, 4);

    // /* =============== TRAINING ================== */
    // Image trainImgs[TRAIN_DATA.SIZE];
    // readImageSet(trainImgs, TRAIN_DATA);
    // transformImageSet(trainImgs, TRAIN_DATA.SIZE, normalize);

    // freeImageSet(trainImgs, TRAIN_DATA.SIZE);
    // /* =========== END OF TRAINING ============== */

    // /* =============== TESTING ================== */
    // Image testImgs[TEST_DATA.SIZE];
    // readImageSet(testImgs, TEST_DATA);
    // transformImageSet(testImgs, TEST_DATA.SIZE, normalize);

    // // WIP

    // freeImageSet(testImgs, TEST_DATA.SIZE);
    // /* =========== END OF TESTING ============== */

    // freeNeuralNet(&nn);

    return 0;
}
