#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "headers/neural_net.h"
#include "headers/matrix.h"

NeuralNetwork createNeuralNet(NeuralNetOpt opt, LayerDesign *layers, int size)
{
    NeuralNetwork nn = { opt, NULL };
    int idx;
    
    if(size < 0) {
        fprintf(stderr, "Neural Network Creation Failed. Size should be a non-negative integer.");
        exit(1);
    }
    
    if(layers != NULL) {
        for(idx = 0; idx < size; idx++) {
            addLayer(&nn, layers[idx].nodes, layers[idx].type);
        }
    }

    return nn; 
}

NeuralNetOpt createNeuralNetOpt(DistType dist, double distSize, double initialBias)
{
    NeuralNetOpt opt = { dist, distSize, initialBias };
    return opt;
}

void fillWeights(Matrix *wts, double distSize, DistType dist)
{
    double mult, bounds;
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
        case ZERO:
            fillMatrix(wts, 0);
            break;
        default:
            fprintf(stderr, "Invalid Weight Type.");
            exit(1);
    }

    if(dist != ZERO) {
        bounds = distSize / sqrt(wts->row * wts->col);
        fillMatrixRandn(wts, -1 * bounds, bounds, mult);
    }
}

Layer createLayer(int nodes, int prevNodes, LayerType type, NeuralNetOpt nnOpt)
{
    if(nodes <= 0 || prevNodes < 0) {
        fprintf(stderr, "Layer Creation Failed. Nodes should be a positive integer.");
        exit(1);
    }

    if (type != INPUT && type != HIDDEN && type != OUTPUT) {
        fprintf(stderr, "Invalid Layer Type.");
        exit(1);
    }

    Layer layer = {
        .nodes = nodes,
        .type = type
    };

    if(prevNodes == 0) {
        layer.weights = createMatrix(0, 0);
        layer.bias = createMatrix(0, 0);
    } else {
        layer.weights = createMatrix(nodes, prevNodes);
        layer.bias = createMatrix(nodes, 1);
        fillWeights(&layer.weights, nnOpt.distSize, nnOpt.dist);
        fillMatrix(&layer.bias, nnOpt.initialBias);
    }

    return layer;
}

void addLayer(NeuralNetwork *nn, int nodes, LayerType type)
{
    int prevLayerNodes = 0;
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

void insertLayer(NeuralNetwork *nn, int position, int nodes, LayerType type)
{
    int prevLayerNodes = 0, idx;
    LayerList *trav, temp;
    
    idx = 1;
    for(trav = &nn->layerList; *trav != NULL && idx < position; trav = &(*trav)->next) {
        prevLayerNodes = (*trav)->layer.nodes;
        idx++;
    }

    // Check if position is not insertable
    if((*trav == NULL && idx < position) || position <= 0) {
        fprintf(stderr, "Invalid position. Can't insert new layer into neural network.");
        exit(1);
    }

    temp = (LayerList) malloc(sizeof(struct LayerNode));
    if(temp == NULL) {
        fprintf(stderr, "Memory allocation failed.");
        exit(1);
    }

    temp->layer = createLayer(nodes, prevLayerNodes, type, nn->options);
    temp->next = *trav;
    *trav = temp;

    // Reinitialize succeeding layer due to the change of nodes
    trav = &(*trav)->next;
    if(*trav != NULL) {
        freeMatrix(&(*trav)->layer.weights);
        freeMatrix(&(*trav)->layer.bias);
        (*trav)->layer = createLayer((*trav)->layer.nodes, temp->layer.nodes, (*trav)->layer.type, nn->options);
    }
}

void deleteLayer(NeuralNetwork *nn, int position)
{
    int idx, prevLayerNodes = 0;
    LayerList *trav, temp;

    idx = 1;
    for(trav = &nn->layerList; *trav != NULL && idx < position; trav = &(*trav)->next, idx++) {
        prevLayerNodes = (*trav)->layer.nodes;
    }

    // Check if position is not deletable
    if(*trav == NULL || position <= 0) {
        fprintf(stderr, "Invalid position. Can't delete layer from neural network.");
        exit(1);
    }
    
    temp = *trav;
    // Reinitialize succeeding layer due to the change of nodes
    *trav = temp->next;
    if(*trav != NULL) {
        freeMatrix(&(*trav)->layer.weights);
        freeMatrix(&(*trav)->layer.bias);
        if(position != 1) {
            (*trav)->layer = createLayer((*trav)->layer.nodes, prevLayerNodes, (*trav)->layer.type, nn->options);
        }
    }
    
    temp->layer.nodes = 0;
    freeMatrix(&temp->layer.bias);
    freeMatrix(&temp->layer.weights);
    free(temp); 
}

void freeNeuralNet(NeuralNetwork *nn)
{
    LayerList *trav, temp;

    for(trav = &nn->layerList; *trav != NULL;) {
        temp = *trav;
        trav = &(*trav)->next;

        temp->layer.nodes = 0;
        freeMatrix(&temp->layer.bias);
        freeMatrix(&temp->layer.weights);
        free(temp); 
    }
}