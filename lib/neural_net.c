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
#include "headers/matrix.h"
#include "headers/doubly_ll.h"
#include "headers/neural_net.h"

#define throwInvalidArgs(arg, msg) { fprintf(stderr, "Invalid %s Argument. %s", arg, msg); exit(1); }
#define throwMallocFailed() { fprintf(stderr, "Memory Allocation Failed."); exit(1); }
#define SHOULD_BE_POSITIVE "It should be a positive integer."
#define SHOULD_BE_NON_NEGATIVE "It should be a non-negative integer."

NeuralNetwork createNeuralNet(NeuralNetOpt opt, LayerDesign *layers, int size)
{
    if(size < 0) throwInvalidArgs("size", SHOULD_BE_POSITIVE);
    
    int idx;
    NeuralNetwork nn = { 
        .options = opt,
        .layers = createList()
    };
    
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
            throwInvalidArgs("distStrat", "");
    }

    if(distStrat != ZERO) {
        bounds = distSize / sqrt(wts->row * wts->col);
        fillMatrixRandn(wts, -1 * bounds, bounds, mult);
    }
}

void activateLayer(Layer *layer, int prevNodes, NeuralNetOpt nnOpt)
{
    if(prevNodes < 0) {
        throwInvalidArgs("prevNodes", SHOULD_BE_NON_NEGATIVE);
    } else if(prevNodes == 0) {
        layer->weights = createZeroMatrix();
        layer->bias = createZeroMatrix();
    } else {
        layer->weights = createMatrix(layer->nodes, prevNodes);
        layer->bias = createMatrix(layer->nodes, 1);
        fillWeights(&layer->weights, nnOpt.distSize, nnOpt.distStrat);
        fillMatrix(&layer->bias, nnOpt.initialBias);
    }
}

void reactivateLayer(Layer *layer, int prevNodes, NeuralNetOpt nnOpt)
{
    if(prevNodes < 0) throwInvalidArgs("prevNodes", SHOULD_BE_NON_NEGATIVE);
    
    freeMatrix(&layer->weights);
    freeMatrix(&layer->bias);
    activateLayer(layer, prevNodes, nnOpt);
}

Layer *createLayer(int nodes, int prevNodes, LayerType type, NeuralNetOpt nnOpt)
{
    if(nodes <= 0) throwInvalidArgs("nodes", SHOULD_BE_POSITIVE)
    if(prevNodes < 0) throwInvalidArgs("prevNodes", SHOULD_BE_NON_NEGATIVE);
    if(type != INPUT && type != HIDDEN && type != OUTPUT) throwInvalidArgs("type", ""); 

    Layer *layer = (Layer *) malloc(sizeof(Layer));
    if(layer == NULL) throwMallocFailed();
    
    layer->nodes = nodes;
    layer->type = type;
    activateLayer(layer, prevNodes, nnOpt);

    return layer;
}

void addLayer(NeuralNetwork *nn, int nodes, LayerType type)
{
    if(nodes <= 0) throwInvalidArgs("nodes", SHOULD_BE_POSITIVE);
    if(type != INPUT && type != HIDDEN && type != OUTPUT) throwInvalidArgs("type", "");

    int prevLayerNodes;
    Layer *prev, *layer;
    
    prev = isListEmpty(nn->layers) ? NULL : (Layer *) getItemByIndex(nn->layers, nn->layers.size - 1);
    prevLayerNodes = prev == NULL ? 0 : prev->nodes;

    layer = createLayer(nodes, prevLayerNodes, type, nn->options);
    addToList(&nn->layers, layer); 
}

void insertLayer(NeuralNetwork *nn, int pos, int nodes, LayerType type)
{
    if(nodes <= 0) throwInvalidArgs("nodes", SHOULD_BE_POSITIVE);
    if(pos <= 0) throwInvalidArgs("pos", SHOULD_BE_POSITIVE);
    if(pos > nn->layers.size + 1) throwInvalidArgs("pos", "It should be bigger than the network size plus one.");
    if(type != INPUT && type != HIDDEN && type != OUTPUT) throwInvalidArgs("type", ""); 
    
    int index, prevLayerNodes;
    Layer *prev, *curr, *next;

    index = pos - 1; // position always starts at 1, index always starts at 0
    prev = isListEmpty(nn->layers) || pos == 1 ? NULL : (Layer *) getItemByIndex(nn->layers, index - 1);
    prevLayerNodes = prev == NULL ? 0 : prev->nodes;
    
    curr = createLayer(nodes, prevLayerNodes, type, nn->options);
    insertToList(&nn->layers, index, curr);

    // Reinitialize succeeding layer
    if(index + 1 < nn->layers.size) {
        next = (Layer *) getItemByIndex(nn->layers, index + 1);
        reactivateLayer(next, curr->nodes, nn->options);
    }
}

void freeLayer(void *item) 
{
    Layer *layer = (Layer *) item;

    layer->type = INPUT;
    layer->nodes = 0;
    freeMatrix(&layer->weights);
    freeMatrix(&layer->bias);
    free(layer);
}

void deleteLayer(NeuralNetwork *nn, int pos)
{
    if(pos <= 0) throwInvalidArgs("pos", SHOULD_BE_POSITIVE);
    if(pos > nn->layers.size) throwInvalidArgs("pos", "It should not be bigger than the layer size.");

    int index, prevLayerNodes;
    Layer *prev, *curr;

    index = pos - 1; // position always starts at 1, index always starts at 0
    deleteFromList(&nn->layers, index, freeLayer);
    
    // Reinitialize previously succeeding layer
    if(index == 1) {
        curr = (Layer *) getItemByIndex(nn->layers, index);
        freeMatrix(&curr->weights);
        freeMatrix(&curr->bias);
    } else if (index < nn->layers.size) {
        curr = (Layer *) getItemByIndex(nn->layers, index);
        prev = isListEmpty(nn->layers) || pos == 1 ? NULL : (Layer *) getItemByIndex(nn->layers, index - 1);
        prevLayerNodes = prev == NULL ? 0 : prev->nodes;
        reactivateLayer(curr, prevLayerNodes, nn->options);
    }
}

void freeNeuralNet(NeuralNetwork *nn)
{
    clearList(&nn->layers, freeLayer);
    nn->options.distSize = 0;
    nn->options.distStrat = ZERO;
    nn->options.initialBias = 0;
}