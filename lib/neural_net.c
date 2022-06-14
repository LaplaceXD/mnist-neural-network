#include <stdlib.h>
#include <math.h>
#include "headers/neural_net.h"
#include "headers/data.h"
#include "headers/matrix.h"

NeuralNetwork createNeuralNet()
{
    return NULL; 
}

void fillWeights(Matrix *wts, WeightInitType init)
{
    double mult;
    int row, col, bound;

    switch(init) {
        case HE:
            mult = sqrt(2.0 / wts->row);
            break;
        case HE_XAVIER:
            mult = sqrt(2.0 / (wts->row + wts->col));
            break;
        case XAVIER:
            mult = sqrt(2.0 / wts->col);
            break;
        case RANDOM:
            mult = 1;
            break;
        case NONE:
            break;
        default:
            fprintf(stderr, "Invalid Weight Type.");
            exit(1);
    }

    if(init != NONE) {
        bound = 1.0 / sqrt(wts->row * wts->col);
        for(row = 0; row < wts->row; row++) {
            for(col = 0; col < wts->col; col++) {
                wts->entries[row][col] = randn(-1 * bound, bound) * mult;
            }
        }
    }
}

Layer createLayer(int nodes, int prevNodes, LayerType type, WeightInitType initWts)
{
    if(nodes <= 0) {
        fprintf(stderr, "Layer Creation Failed. Nodes should be a positive integer.");
        exit(1);
    }
    
    Layer layer = {
        .nodes = nodes,
        .type = type,
    };

    switch(type) {
        case INPUT:
            layer.weights = createMatrix(0, 0);
            layer.bias = createMatrix(0, 0);
            break;
        case HIDDEN:
        case OUTPUT:
            layer.weights = createMatrix(nodes, prevNodes);
            layer.bias = createMatrix(nodes, 1);
            fillWeights(&layer.weights, initWts);
            break;
        default:
            fprintf(stderr, "Invalid Layer Type.");
            exit(1);
    }

    return layer;
}

void addLayer(NeuralNetwork *nn, int nodes, LayerType type, WeightInitType initWts)
{
    int prevLayerNodes;
    NeuralNetwork *trav, temp;

    for(trav = nn; *trav != NULL; trav = &(*trav)->next) {
        prevLayerNodes = (*trav)->layer.nodes;
    }

    temp = (NeuralNetwork) malloc(sizeof(struct LayerNode));
    if(temp == NULL) {
        fprintf(stderr, "Memory allocation failed.");
        exit(1);
    }

    temp->layer = createLayer(nodes, prevLayerNodes, type, initWts);
    temp->next = NULL;
    *trav = temp;
}

void freeNeuralNet(NeuralNetwork *nn)
{
    NeuralNetwork temp;

    while(*nn != NULL) {
        temp = *nn;
        *nn = temp->next;

        temp->layer.nodes = 0;
        freeMatrix(&temp->layer.bias);
        freeMatrix(&temp->layer.weights);
        free(temp); 
    }
}