#include <stdlib.h>
#include <math.h>
#include "headers/neural_net.h"
#include "headers/data.h"
#include "headers/matrix.h"

NeuralNetwork createNeuralNet(NeuralNetOpt opt)
{
    NeuralNetwork nn = { opt, NULL };
    return nn; 
}

void fillWeights(Matrix *wts, double distSize, DistType dist)
{
    double mult, bound;
    int row, col;

    switch(dist) {
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
        default:
            fprintf(stderr, "Invalid Weight Type.");
            exit(1);
    }

    bound = distSize / sqrt(wts->row * wts->col);
    for(row = 0; row < wts->row; row++) {
        for(col = 0; col < wts->col; col++) {
            wts->entries[row][col] = randn(-1 * bound, bound) * mult;
        }
    }
}

Layer createLayer(int nodes, int prevNodes, LayerType type, NeuralNetOpt nnOpt)
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
            fillWeights(&layer.weights, nnOpt.distSize, nnOpt.dist);
            fillMatrix(&layer.bias, 0);
            break;
        default:
            fprintf(stderr, "Invalid Layer Type.");
            exit(1);
    }

    return layer;
}

void addLayer(NeuralNetwork *nn, int nodes, LayerType type)
{
    int prevLayerNodes;
    LayerList *trav, temp;

    for(trav = &nn->layerList; *trav != NULL; trav = &(*trav)->next) {
        prevLayerNodes = (*trav)->layer.nodes;
    }

    temp = (LayerList) malloc(sizeof(struct LayerNode));
    if(temp == NULL) {
        fprintf(stderr, "Memory allocation failed.");
        exit(1);
    }

    temp->layer = createLayer(nodes, prevLayerNodes, type, nn->options);
    temp->next = NULL;
    *trav = temp;
}

void freeNeuralNet(NeuralNetwork *nn)
{
    LayerList *trav, temp;

    for(trav = &nn->layerList; *trav != NULL; trav = &(*trav)->next) {
        temp = *trav;

        temp->layer.nodes = 0;
        freeMatrix(&temp->layer.bias);
        freeMatrix(&temp->layer.weights);
        free(temp); 
    }
}