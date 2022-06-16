/** @file neural_net.c
 *  @brief A library made for working with neural networks.
 *  This has a dependency to matrix.c library.
 * 
 *  This library contains various functions which allows
 *  users to create neural networks. It also has functions
 *  for creating, deleting, and inserting layers. 
 *
 *  @author Jonh Alexis Buot (LaplaceXD)
 *  @bug No know bugs.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "headers/neural_net.h"
#include "headers/matrix.h"

#define throw(err) { fprintf(stderr, "%s\n", err); exit(1); }

typedef struct ErrorMessages {
    char *INVALID_SIZE;
    char *INVALID_DIST_STRAT;
    char *INVALID_LAYER_SHAPE;
    char *INVALID_LAYER_TYPE;
    char *INVALID_POSITION;
    char *FAILED_MEMORY_ALLOCATION;
} ErrorMessages;

const ErrorMessages ERROR = {
    .INVALID_SIZE = "Neural Network Creation Failed. Invalid Size Argument. It should be a non-negative integer.",
    .INVALID_DIST_STRAT = "Neural Network Creation Failed. Invalid Distribution Strategy.",
    .INVALID_LAYER_SHAPE = "Layer Creation Failed. Invalid Node Argument should be a non-negative integer.",
    .INVALID_LAYER_TYPE = "Layer Creation Failed. Invalid Layer Type.",
    .INVALID_POSITION = "Invalid Postion Argument should be a positive integer.",
    .FAILED_MEMORY_ALLOCATION = "Memory Allocation Failed."
};

NeuralNetwork createNeuralNet(NeuralNetOpt opt, LayerDesign *layers, int size)
{
    if(size < 0) throw(ERROR.INVALID_SIZE);
    
    NeuralNetwork nn = { opt, NULL };
    int idx;
    
    if(layers != NULL) {
        for(idx = 0; idx < size; idx++) {
            addLayer(&nn, layers[idx].nodes, layers[idx].type);
        }
    }

    return nn; 
}

void fillWeights(Matrix *wts, double distSize, DistStrategy distStrat)
{
    double mult, bounds;
    int row, col;

    switch(distStrat) {
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
            throw(ERROR.INVALID_DIST_STRAT)
    }

    if(distStrat != ZERO) {
        bounds = distSize / sqrt(wts->row * wts->col);
        fillMatrixRandn(wts, -1 * bounds, bounds, mult);
    }
}

Layer createLayer(int nodes, int prevNodes, LayerType type, NeuralNetOpt nnOpt)
{
    if(nodes <= 0 || prevNodes < 0) throw(ERROR.INVALID_LAYER_SHAPE);
    if(type != INPUT && type != HIDDEN && type != OUTPUT) throw(ERROR.INVALID_LAYER_TYPE); 

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
        fillWeights(&layer.weights, nnOpt.distSize, nnOpt.distStrat);
        fillMatrix(&layer.bias, nnOpt.initialBias);
    }

    return layer;
}

void reinitializeLayer(Layer *layer, int prevLayerNodes, NeuralNetOpt nnOpt)
{
    if(prevLayerNodes < 0) throw(ERROR.INVALID_LAYER_SHAPE);

    Layer newLayer = createLayer(layer->nodes, prevLayerNodes, layer->type, nnOpt);    
    free(&layer->weights);
    free(&layer->bias);
    *layer = newLayer;
}

void addLayer(NeuralNetwork *nn, int nodes, LayerType type)
{
    if(nodes < 0) throw(ERROR.INVALID_LAYER_SHAPE);
    if(type != INPUT && type != HIDDEN && type != OUTPUT) throw(ERROR.INVALID_LAYER_TYPE); 
    
    int prevLayerNodes = 0;
    LayerList *trav, temp;

    for(trav = &nn->layerList; *trav != NULL; trav = &(*trav)->next) {
        prevLayerNodes = (*trav)->layer.nodes;
    }

    temp = (LayerList) malloc(sizeof(struct LayerNode));
    if(temp == NULL) throw(ERROR.FAILED_MEMORY_ALLOCATION);

    temp->layer = createLayer(nodes, prevLayerNodes, type, nn->options);
    temp->next = NULL;
    *trav = temp;
}

void insertLayer(NeuralNetwork *nn, int position, int nodes, LayerType type)
{
    if(nodes < 0) throw(ERROR.INVALID_LAYER_SHAPE);
    if(position <= 0) throw(ERROR.INVALID_POSITION);
    if(type != INPUT && type != HIDDEN && type != OUTPUT) throw(ERROR.INVALID_LAYER_TYPE); 
    
    int prevLayerNodes, idx;
    LayerList *trav, temp;

    idx = 1;
    prevLayerNodes = 0; 
    for(trav = &nn->layerList; *trav != NULL && idx < position; trav = &(*trav)->next) {
        prevLayerNodes = (*trav)->layer.nodes;
        idx++;
    }

    if(idx < position && *trav == NULL) throw(ERROR.INVALID_POSITION);

    temp = (LayerList) malloc(sizeof(struct LayerNode));
    if(temp == NULL) throw(ERROR.FAILED_MEMORY_ALLOCATION);

    temp->layer = createLayer(nodes, prevLayerNodes, type, nn->options);
    temp->next = *trav;
    *trav = temp;

    // Reinitialize succeeding layer due to the change of nodes
    trav = &(*trav)->next;
    if(*trav != NULL) {
        reinitializeLayer(&(*trav)->layer, prevLayerNodes, nn->options);
    }
}

void deleteLayer(NeuralNetwork *nn, int position)
{
    if(position <= 0) throw(ERROR.INVALID_POSITION);
    
    int idx, prevLayerNodes;
    LayerList *trav, temp, nextLayer;

    idx = 1;
    prevLayerNodes = 0;
    for(trav = &nn->layerList; *trav != NULL && idx < position; trav = &(*trav)->next) {
        prevLayerNodes = (*trav)->layer.nodes;
        idx++;
    }

    if(*trav == NULL) throw(ERROR.INVALID_POSITION);
    temp = *trav;
    *trav = temp->next;
    
    freeMatrix(&temp->layer.bias);
    freeMatrix(&temp->layer.weights);
    free(temp); 
    
    // Reinitialize succeeding layer due to the change of nodes
    if(*trav != NULL) {
        if(position == 1) {
            freeMatrix(&(*trav)->layer.weights);
            freeMatrix(&(*trav)->layer.bias);
        } else {
            reinitializeLayer(&(*trav)->layer, prevLayerNodes, nn->options);
        }
    }
}

void freeNeuralNet(NeuralNetwork *nn)
{
    LayerList *trav, temp;

    for(trav = &nn->layerList; *trav != NULL;) {
        temp = *trav;
        trav = &(*trav)->next;

        freeMatrix(&temp->layer.bias);
        freeMatrix(&temp->layer.weights);
        free(temp); 
    }
}